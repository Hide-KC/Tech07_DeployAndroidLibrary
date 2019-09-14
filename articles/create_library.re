= ライブラリモジュールの作成とアップロード

この章では、ライブラリを作るためのモジュールの生成及び Gradle による AAR（Android Archives）ファイルへのコンパイルについて説明します。

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

まずは公開用の Android ライブラリを作るため、いつもどおりプロジェクトを作成します。
最初の Activity の選択は "Add no Activity" でもなんでも結構です。

ここではプロジェクトの名称を "HelloWorldLibrary" としましょう。

//image[select_activity][New Project][scale=0.64]{
//}

== ライブラリモジュールの作成

プロジェクトの作成が完了したら、次にライブラリ用のモジュールを作成します。
HelloWorldLibrary プロジェクトを開いた状態で `File → New → New Module` を選択し、一覧の中から `Android Library` を選択します。

//image[create_module][New Module - Android Library を選択する][scale=0.64]{
//}

次にモジュールの情報を入力しますが、"Module Name" と "Package Name" は AAR ファイルのコンパイル時にファイル名として使用されるため、本来はよく考える必要があります。
しかし、今回は

//image[configure_module][Configure Module - モジュールの設定][scale=0.64]{
//}

== クラスの作成

== Gradle ファイルの記述



