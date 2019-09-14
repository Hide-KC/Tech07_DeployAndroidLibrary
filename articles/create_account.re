= Bintray への登録と API キーの取得

作成したライブラリの公開のため、ホスティングサービスの Bintray@<fn>{bintray} を利用します。
Bintray は OSS 専用のアカウントであれば無料で利用することができます。

//footnote[bintray][Bintray https://bintray.com/]

== OSS アカウントの登録

まずは Bintray の OSS アカウントを登録します。

//image[bintray_signup][Bintray OSS アカウントの登録][scale=0.64]{
//}

GitHub アカウントと連携すると何かと都合がいいので、そちらを利用するのでもよいでしょう。

== Maven リポジトリの作成

アカウントの作成が終わったら、次にライブラリをアップロードするための Maven リポジトリを作成します。
Add New Repository をクリックし、必要な情報を入力します。

//image[add_new_repo][Add New Repository][scale=0.64]{
//}

//image[config_repo][リポジトリの情報の入力][scale=0.64]{
//}

ここでは、リポジトリの種類を "Maven"、ライセンスを "MIT" としました。
Create をクリックするとリポジトリが生成されます。

== API キーの取得

Maven リポジトリの作成が終わったら、次に Gradle からアクセスするための API キーを取得します。
右上のメニューから Edit Profile をクリックします。

//image[edit_profile][Edit Profile][scale=0.64]{
//}

そして、左側のメニューから API Key をクリックし、API キーを確認します（"Show" をクリックすると表示されます）。

//image[api_key][API Key][scale=0.64]{
//}

== gradle.properties への保存

@<code>{~/.gradle/gradle.properties} に先ほどの API キーを保存します。

//listnum[gradle_properties][API キーの保存]{
bintray_user=<Your userId>
bintray_key=<Your API key>
//}

これで Bintray 側の準備が終わりました。
次に Android Studio でライブラリを作成していきます。