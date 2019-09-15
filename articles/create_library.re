= ライブラリモジュールの作成とアップロード

ライブラリモジュールの生成及び Gradle による AAR（Android Archives）ファイルへのコンパイルについて説明します。

== どんなライブラリを作るか

@<list>{eg_library}に示すクラスをもつライブラリです。

//listnum[eg_library][HelloWorldCore.kt]{
package work.kcs_labo.helloworld

class HelloWorldCore {
  fun getHello(message: String) : String {
    return "Hello, $message!"
  }
}
//}

@<code>{getHello} メソッドのみをもつ非常に単純なライブラリです。
それではさっそく作っていきましょう。

== プロジェクトの作成

まずはいつもどおりの手順で Android プロジェクトを作成します。
最初の Activity の選択は "Add no Activity" でもなんでも結構です。
ここではプロジェクトの名称を "HelloWorldLibrary" としましょう。

//image[select_activity][New Project][scale=0.64]{
//}

== ライブラリモジュールの作成

次にライブラリ用のモジュールを作成します。
HelloWorldLibrary プロジェクトを開いた状態で `File → New → New Module` を選択し、一覧の中から `Android Library` を選択します。

//image[create_module][New Module - Android Library を選択する][scale=0.64]{
//}

ここでモジュールの情報を入力しますが、"Module Name" と "Package Name" は次のように使用されます。

//list[dependencies][モジュール情報の利用先]{
//Module Name は AAR ファイルの名前に使われる
{Module Name}-1.0.0.aar

//Package Name はインポートに使われる
import {Package Name}.Utils;
//}

本来はどういった AAR ファイルで配布したいか、ライブラリのインポートの記述はどのようにしたいかをよく考えて決定しなければなりませんが、今回はサンプルなのであまり深く考えなくて大丈夫です。

//image[configure_module][モジュールの設定][scale=1.0]{
//}

== クラスの作成

次に処理を実装します。
いつもどおり @<code>{src/main} に記述すればOKです。
ここでは前述のとおり @<code>{HelloWorldCore} を実装しました。

//listnum[eg_library2][HelloWorldCore.kt（再掲）]{
package work.kcs_labo.helloworld

class HelloWorldCore {
  fun getHello(message: String) : String {
    return "Hello, $message!"
  }
}
//}

== Gradle ファイルの記述

それではメインの Gradle ファイルの記述を見ていきますが、最初に必要なプラグインを紹介します。

=== 利用するプラグイン

 * maven-publish
 ** ビルドしたファイルを Maven リポジトリに出力するプラグイン
 * org.jetbrains.dokka-android
 ** Kotlin で書いたソースから JavaDoc を生成するプラグイン
 * com.jfrog.bintray
 ** Bintray にアップロードするためのプラグイン

以降の各プラグインのバージョンは執筆時点の最新安定版になります。

=== プロジェクトレベル build.gradle

プラグインを使用するため、プロジェクトレベルの build.gradle に次の記述を追加します。

//listnum[project_build.gradle][クラスパスの追加]{
dependencies {
  classpath 'com.jfrog.bintray.gradle:gradle-bintray-plugin:1.8.4'
  classpath 'com.github.dcendents:android-maven-gradle-plugin:2.1'
  classpath 'org.jetbrains.dokka:dokka-android-gradle-plugin:0.9.18'
}
//}

=== モジュールレベル build.gradle

次にモジュールレベルの build.gradle の末尾に次の記述を追加します。

//listnum[module_build.gradle][依存関係の指定]{
apply from: 'deploy.gradle'
//}

deploy.gradle は AAR ファイルのビルドを行ったり、Maven リポジトリへのアップロードを行うための Gradle ファイルです。
現時点では存在しないと思いますので、モジュール内に deploy.gradle を作成しておきましょう。

//image[create_deploy][deploy.gradle の生成][scale=1.0]{
//}

=== deploy.gradle

次に deploy.gradle の記述を見ていきましょう。
deploy.gradle の全体は付録に載せておきましたので、そちらも見ながら読み進めてみてください。
ここではポイントを絞って説明します。

==== AAR と JavaDoc の生成

まずは @<code>{soucesJar} タスクと @<code>{javadocJar} タスクです。
これらのタスクにより、AAR 及び JavaDoc の生成を行っています。

//listnum[sourcesjar][AAR と JavaDoc の生成]{
dokka {
  outputFormat = 'javadoc'
  outputDirectory = "$buildDir/javadoc"
}

task sourcesJar(type: Jar) {
  classifier = 'sources'
  from android.sourceSets.main.java.srcDirs
}

task javadocJar(type: Jar, dependsOn: dokka) {
  classifier = 'javadoc'
  from "$buildDir/javadoc"
}
//}

==== loadProperties メソッド

~/.gralde/gradle.properties に保存した API キーを取得するため、loadProperties メソッドを定義しています。

//listnum[loadproperties][loadProperties メソッド]{
def loadProperties(filename) {
  def props = new Properties()
  file(filename).withInputStream {
    props.load(it)
  }
  return props
}

//使用例
def props = loadProperties("$gradle.gradleUserHomeDir/gradle.properties")
//}

==== ローカル Maven リポジトリに発行する publishing クロージャ

maven-publish のタスク @<code>{publish} で、Maven リポジトリに発行するための設定を記述したクロージャです。

//listnum[publishing][publishing クロージャ]{
project.afterEvaluate {
  publishing {
    publications {
      //"bintray" の部分は myBintray でもなんでもOK
      bintray(MavenPublication) {
        ...
        //配布物としてリポジトリに含めるファイル
        artifact sourcesJar
        artifact javadocJar
        artifact bundleReleaseAar

        //出力する POM の設定
        pom.withXml {
          def root = asNode()
          root.appendNode('description', libDescription)
          root.appendNode('name', libName)
          root.appendNode('url', siteUrl)
          root.children().last() + pomConfig

          //依存関係は明示的に指定しないと POM に含まれない
          def dependenciesNode = root['dependencies'][0] ?:
                                   root.appendNode('dependencies')
          configurations.implementation.allDependencies.each {
            // Ensure dependencies such as fileTree are not included.
            if (it.name != 'unspecified') {
              def dependencyNode = dependenciesNode.appendNode('dependency')
              dependencyNode.appendNode('groupId', it.group)
              dependencyNode.appendNode('artifactId', it.name)
              dependencyNode.appendNode('version', it.version)
            }
          }
        }
      }
    }
    //出力先のパス（ローカル）を指定
    repositories {
      maven {
        url "$buildDir/repo"
      }
    }
  }
}
//}

pom.withXml クロージャにおいて asNode メソッドを使用することにより、groovy.util.Node 形式で取得できます。
取得したオブジェクトに対し、appendNode メソッドで必要な要素を追加していきます。

ここでひとつ注意したいのが、依存関係は明示的に記述しないと出力されない点です。
依存している外部ライブラリがある場合は dependenciesNode 以降の記述を忘れないようにしましょう。

==== publish タスクの実行

ここまで記述が終わったら、maven-publish の publish タスクを実行しローカル Maven リポジトリに発行してみましょう。
Android Studio でターミナルを開き、次のコマンドを実行します。

//cmd{
# gradlewが置いてあるディレクトリに移動
$ cd <Project root>

# リビルド → パブリッシュ
$ gradlew clean build publish
//}

無事にターミナルに "Build Successful" が表示されれば、次のように build フォルダ配下のローカル Maven リポジトリにファイルが発行されます。

//image[publish_tree][publish 後の build フォルダ][scale=0.84]{
//}

配布物となる AAR、JavaDoc ファイルは確認できましたでしょうか。
次の章では、 Bintray のリモート Maven リポジトリにファイルをアップロードし、ライブラリとして公開していきます。