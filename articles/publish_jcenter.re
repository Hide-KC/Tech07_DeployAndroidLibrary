= JCenter への登録と利用

本章では Bintray の Maven リポジトリにライブラリをアップロードします。
そして JCenter に登録し、次のように dependencies に１行追記するだけでライブラリを使用できるようにします。

//listnum[append_dependency][依存関係の追加]{
repositories {
  JCenter()
}

dependencies {
  implementation 'work.kcs_labo:helloworldlibrary:0.0.1'
}
//}

== bintray クロージャの追加

Bintray にアップロードするため、deploy.gradle に bintray クロージャを追加します。
ライブラリはリモートリポジトリの中の "パッケージ" という単位で公開されますが、そのパッケージの情報を pkg クロージャに記述します。

//listnum[bintray][bintray クロージャ]{
bintray {
  ...
  //publishing.publications で記述した bintray を指定
  publications = ['bintray']

  //リモート Maven リポジトリに追加するパッケージの設定
  pkg {
    repo = 'maven'
    name = libName
    desc = libDescription
    publish = true
    override = true
    userOrg = devId
    licenses = [licenseName]
    vcsUrl = siteUrl + '.git'
    version {
      name = libVersion
    }
  }
}
//}

== アップロードコマンドの実行

deploy.gradle の記述が完了したら、次のコマンドで build/repo の AAR や JAR ファイルをアップロードします。

//listnum[bintrayupload][アップロードコマンド]{
$ gradlew bintrayUpload
//}

自身のアカウントの Maven リポジトリに HelloWorld パッケージが追加され、Files タブで AAR 等がアップロードされているのが確認できましたでしょうか。

//image[upload_files][アップロードされたファイルの確認][scale=0.84]{
//}

== JCenter への登録申請

それでは JCenter に登録してみましょう。
パッケージページの右下にある "Add to JCenter" をクリックすると、次の画面が表示されます。

//image[jcenter_send][caption][scale=0.84]{
//}

"is pom project" 及び "Host my snapshot ~" にチェックを入れると、GroupId の入力ボックスが表示されるので、HelloWorldLibrary の groupId を入力してください。
一意性を求められますが、モジュールの作成時点で一意になっているはずなのでそのまま入力しましょう。

審査には１日～２日程度かかる模様なので、気長に待ちましょう。
万が一リジェクトされた場合でも、理由がメッセージで送られてきますので粛々と対応しましょう。

== ライブラリの利用

無事に JCenter に登録できたら、適当な Android プロジェクトに依存関係を追加して確認してみましょう。

//listnum[append_dependency2][依存関係の追加（再掲）]{
repositories {
  JCenter()
}

dependencies {
  implementation 'work.kcs_labo:helloworldlibrary:0.0.1'
}
//}

テスト等で HelloWorldCore クラスが参照できれば完了です。
お疲れさまでした。