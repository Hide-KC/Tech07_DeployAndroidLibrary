= JCenter への登録と利用

== 生成ファイルの確認

== bintray クロージャの追加

==== Bintray にアップロードする bintray クロージャ

最後に Bintray にアップロードするための設定を記述した bintray クロージャです。

//listnum[bintray][bintray クロージャ]{
bintray {
  def props = loadProperties("$gradle.gradleUserHomeDir/gradle.properties")

  //ユーザ ID と API キーを取得
  user = props.bintray_user
  key = props.bintray_key
  
  //publishing.publications クロージャで記述した bintray を指定
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
      //name のみ必須パラメータ
      name = libVersion
    }
  }
}
//}

Bintray のリモート Maven リポジトリではパッケージという単位でライブラリが公開されますが、その情報を記述します。


== アップロードコマンドの実行

== JCenter への登録申請

== ライブラリの利用