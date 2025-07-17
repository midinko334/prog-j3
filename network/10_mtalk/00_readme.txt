10_mtalk

----- ----- ----- ----- ----- 
課題0：演習準備

ディレクトリ 10_mtalk をコピーする。

../mylib の修正
  ../mylib/Makefile の修正
    OBJS への代入のところでコメント アウトされていた setup_mserver.o を有効
にする．
  ../mylib にて、makeコマンドを実行して
  mylib.a を再生成する。

----- ----- ----- ----- ----- 
課題1：Makefile の作成

10_mtalk に、以下の仕様のMakefile を作成する。


環境変数 MYLIBDIR に以下をセットする。
    ../mylib

環境変数 MYLIB に以下をセットする。
    $(MYLIBDIR)/mylib.a

環境変数 CFLAGS に以下をセットする。
    -I$(MYLIBDIR)

環境変数 BIN に以下をセットする。
    server
    client
    server.mod
    client.mod

フォニーターゲット all と clean を作成する。

依存関係：
server.o ->
  sessionman.h
server.mod.o ->
  session.h
client.o ->
  session.h
client.mod.o ->
  session.h
server ->
  server.o
  sessionman.o
client ->
  client.o
  session.o
server.mod ->
  server.o
  sessionman.mod.o
client.mod ->
    client.mod.o
    session.mod.o

コンパイルルールに $(MYLIB) -lcurses を記述する。

----- ----- ----- ----- ----- 
課題2：ミニ電子会議システムのサーバとクライアント

- ソースコードの完成
session.h
sessionman.h
  ポート番号の定義
server.c
  引数の処理部分を完成させる。
session.c
  FD_ISSET マクロの引数の部分を埋める。
  ★「Wait for initializing.」と表示する処理と、バックスペースの処理の実装に
    ついては session.mod.c で行うので、session.c では未実装のままとする。
sessionman.c
  ソケットからの入力について調べる処理を実装する。
  全てのクライアントに「quit」を送信する部分を実装する。
  ★ソケットからの入力に、もしも改行コードが複数ある場合は再読み込みをするが、
    それは sessionman.mod.c にて実装するので、sessionman.c では未実装のままと
    する。
- make server
- make client

動作確認：
(0)
  3個の端末(端末0,1,2とする）を用意する。
  端末0：サーバ用
  端末1：会議参加者1 のクライアント用
  端末2：会議参加者2 のクライアント用
(1)
  端末0 で server を起動する。
  第1引数：会議参加者数（ここでは 2）
(2)
  端末1 と端末2 で client を起動する。
  ウィンドウのサイズを調整したときは、session.c で定義されている
  RECV_WIN_HEIGHT の値を変更する。

----- ----- ----- ----- ----- 
課題3：ミニ電子会議システムの改良

開発手順：
- ソースコードの再利用のためにコピーする。
    cp client.c client.mod.c
    cp session.c session.mod.c
    cp sessionman.c sessionman.mod.c

改良点：
client.mod.c
  サーバのホスト名をコマンドラインにて引数として与える。

session.mod.c
 - 「Wait for initialising.」と表示する。
 - バックスペースの処理を実装する。

sessionman.mod.c
 - 名前を入力するためのプロンプトが表示される前に、何行か文字列を入力する
   と，挙動がおかしくなる。
 - たとえば、端末1 で client を実行し、端末2 でも client を実行したとき、
   本来は、先に実行した端末1 での client で名前を入力し終わるのを待って
   から端末2 で名前を入力して電子会議が開始される。
 - ところが、端末1 で client を実行し、端末2 でも client を実行したときに、
   端末2 で名前を入力し、いくつかのメッセージも何行分か入力した後に、端末1
   で名前を入力して電子会議が開始されると、端末2 の挙動がおかしくなる。
   おかしな挙動が起こることを確認する。
 - そこで、以下のような処理を実装する：
    * select() を用いて、ソケットにデータが到来しているか調べる。
    * もしもデータが到来してれいば、全て読み込む。
    * 念のため、この一連の処理を while 文にて反復する。
 ★なお，1行は16文字以下であることを仮定してよい．

動作確認：
　課題2 と同様に server.mod と client.mod の動作を確認する。

## EOF
