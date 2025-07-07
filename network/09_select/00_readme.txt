09_select

----- ----- ----- ----- ----- 
課題0：演習準備

  ディレクトリ 09_select をコピーする。

  09_select の中に以下のシンボリック リンクを作成する。
    ../01_TCPecho/DieWithError.c
    ../01_TCPecho/HandleTCPClient.c
    ../07_multitask/AcceptTCPConnection.c
    ../07_multitask/CreateTCPServerSocket.c

----- ----- ----- ----- ----- 
課題1：Makefile の作成

09_select に、以下の仕様のMakefile を作成する。

環境変数 INCLUDE に以下をセットする。
  ../include

環境変数 MYLIBDIR に以下をセットする。
  ../mylib

環境変数 CFLAGS に以下をセットする。
  -I$(INCLUDE) -I$(MYLIBDIR)

環境変数 MYLIB に以下をセットする。
  $(MYLIBDIR)/mylib.a

環境変数 BIN に以下をセットする。
  TCPEchoServer-Select
  tag_server
  tag_client
  tag_server.mod
  tag_client.mod

フォニーターゲット all と clean を作成する、

依存関係：
TCPEchoServer-Select.o ->
  $(INCLUDE)/TCPEchoServer.h
tag_server.o ->
  tag.h
  tag_session.h
tag_client.o ->
  tag.h
  tag_session.h
tag_server.mod.o ->
  tag.h
  tag_session.h
tag_client.mod.o ->
  tag.h
  tag_session.h
TCPEchoServer-Select ->
  AcceptTCPConnection.o
  CreateTCPServerSocket.o
  DieWithError.o
  HandleTCPClient.o
  TCPEchoServer-Select.o
tag_server ->
  tag_server.o
  tag_session.o
tag_client ->
  tag_client.o
  tag_session.o
tag_server.mod ->
  tag_server.mod.o
  tag_session.mod.o
tag_client.mod ->
  tag_client.mod.o
  tag_session.mod.o

鬼ごっこ(4個)について
  コンパイルルールに $(MYLIB) -lcurses を記述する。

----- ----- ----- ----- ----- 
課題2：TCPEcho-Server-Select の完成
- ソースコードの穴埋め
    TCPEchoServer-Select.c
- make TCPEcho-Server-Select
- TCPEcho-Server-Select の動作確認

動作確認方法：01_TCPecho/TCPEchoClient をクライアントとして用いる。
(0)
  3個の端末（端末0,1,2とする）を用意する。
(1)
  端末0 で TCPEchoServer-Select を起動する。
  第1引数：タイムアウト時間（秒単位）
  第2引数：ポート番号 portA - 学籍番号からハイフンを除いた数値
  第3引数：ポート番号 portB - portA に 10000 を足した数値
(2)
  端末1 で、portA を使用するように、クライアントを実行する。
(3)
  端末2 で、portB を使用するように、クライアントを実行する。
(4)
  何回か(2)と(3)を実行して、両者が並列実行することを確認する。
  また、サーバ側が表示するポート番号が変化することを確認する。
(5)
  端末0 にて Enter キーを入力し、サーバを終了する。
  

----- ----- ----- ----- ----- 
課題3：鬼ごっこプログラムの実行
- tag.h の修正（ポート番号）
- make TCPEcho-Server-Select
- 動作確認

動作確認方法：
(0)
  2個の端末（端末0,1,2とする）を用意する。
(1)
  端末0 で tag_server を起動する（o:人）。
(2)
  端末1 で tag_client を起動する（x:鬼）。
(3)
  端末0, 1でキー操作を行い、人間と鬼の動作を確認

キー操作：
  h：左に動く
  j：下に動く
  k：上に動く
  l：右に動く
  q：終了


----- ----- ----- ----- ----- 
課題4：鬼ごっこプログラムの修正と拡張

拡張機能：
- ホスト名をコマンドライン引数で与えるようにする。
- 開始時に、相手も表示する。
- 鬼に人が捕まったらプログラム終了する。
- 開始時に、人と鬼をランダムな位置に出現させる。

開発手順：
- ソースコードを再利用数ためにコピーする
    cp tag_server.c tag_server.mod.c
    cp tag_client.c tag_client.mod.c
    cp tag_session.c tag_session.mod.c
- ソースコードの修正
    tag_server.mod.c, tag_client.mod.c, tag_session.mod.c を修正

時間が余ったら、以下のような、ゲーム性を高める機能を追加してみましょう。
- 一定時間逃げ切ったら人の勝ちとする。
- サーバに自動で逃げ回るモードを追加して、1人で遊べるようにする。
  - たとえば、ランダムに動く
  - たとえば、鬼から離れるように動く
- 障害物を置く。障害物を増やして迷路状にする。
- 体力を導入する。
  - 体力がなくなったら動けなくなる。
  - 体力を増やすアイテムを導入する。
  - 人にワープする機能（体力消耗が大きい）
- など、など

## EOF
