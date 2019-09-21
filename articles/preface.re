= はじめに

本書を手に取っていただき、ありがとうございます。
この本では、Android 用自作ライブラリを JCenter に公開するための手順をまとめました。

== 対象読者

 * Android 用の自作ライブラリを作って公開したい方
 * Gradle の記述で挫折してしまった方

== 本書の内容

 1. Android Studio でライブラリを作る
 1. Gradle で Bintray の Maven リポジトリにアップロードする
 1. JCenter にライブラリを公開する

== 本書の環境

 * Windows 10 Pro
 * Android Studio 3.5
 * Gradle 5.4.1
 ** Gradle Wrapper を使うので個別にインストールは不要です
 * Kotlin 1.3.21

== 免責事項

本書（紙および電子媒体を含む。以下同様。）にコード等を掲載するにあたって、
その内容、機能等について細心の注意を払っておりますが、掲載の内容が正確であるかどうか、
最新のものであるかどうか、安全なものであるか等について保証をするものではなく、
何らの責任を負うものではありません。

また、本書を用いてアプリケーション等を製作したことにより、
万一、製作者様に何らかの不都合や損害が発生したとしても、
著者は何らの責任を負うものではないことをあらかじめご承知おきください。

本書に掲載されているあらゆる内容の著作権は著者に帰属しており、
他のホームページ・ブログ・SNS等に無断で転載・転用することを禁止します。
引用する場合は、タイトルおよび著者等を明示して本書からの引用であることを明らかにしてください。

== 参考サイト

 * Bintray https://bintray.com/
 * Maven Publish Plugin https://docs.gradle.org/current/userguide/publishing_maven.html
 * bintray plugin https://github.com/bintray/gradle-bintray-plugin
 * dokka plubin https://github.com/Kotlin/dokka
 * 執筆者の Bintray アカウント https://bintray.com/hide-kc
