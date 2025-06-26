08_thread_ForkN

----- ----- ----- ----- ----- 
課題0：演習準備

  ディレクトリ 08_thread_ForkN をコピーする。

  08_thread_ForkN の中に以下のシンボリック リンクを作成する。
    ../01_TCPecho/DieWithError.c
    ../01_TCPecho/HandleTCPClient.c
    ../07_multitask/AcceptTCPConnection.c
    ../07_multitask/CreateTCPServerSocket.c


----- ----- ----- ----- ----- 
課題1：Makefile の作成

08_thread_ForkN に、以下の仕様のMakefile を作成する。

環境変数 INCLUDE に以下をセットする。
  ../include

環境変数 CFLAGS に以下をセットする。
 -I$(INCLUDE)

環境変数 BIN に以下をセットする。
  TCPEchoServer-Thread
  TCPEchoServer-ForkN

TCPEchoServer-Thread について
  コンパイルルールに -pthread を記述する。

依存関係：
TCPEchoServer-Thread.o ->
  $(INCLUDE)/TCPEchoServer.h
TCPEchoServer-ForkN.o ->
  $(INCLUDE)/TCPEchoServer.h
TCPEchoServer-Thread ->
    AcceptTCPConnection.o
    CreateTCPServerSocket.o
    DieWithError.o
    HandleTCPClient.o
    TCPEchoServer-Thread.o
TCPEchoServer-ForkN
    AcceptTCPConnection.o
    CreateTCPServerSocket.o
    DieWithError.o
    HandleTCPClient.o
    TCPEchoServer-ForkN.o


----- ----- ----- ----- ----- 
課題2：TCPEchoServer-Thread の完成
- ソースコードファイルの穴埋め
    TCPEchoServer-Thread.c
- make TCPEchoServer-Thread
- TCPEchoServer-Thread の動作確認

動作確認方法：,,/01_TCPecho/TCPEchoClient をクライアントとして用いる。
(0)
  複数の端末（端末0,1,2... とする）を用意する。

(1)
  端末0 で TCPEchoServer-Thread を実行する。

(2)
  端末1,2... で、クライアントの実行する。

(3)
  何回かクライアントを実行すると、サーバが1つずつ処理することを確認する。
  （サーバ動作を遅延するため sleep 関数を挿入する必要がある場合がある）

(4)
  サーバを停止する（Ctrl-C）


----- ----- ----- ----- ----- 
課題3：TCPEchoServer-ForkN の完成
- ソースコードファイルの穴埋め
    TCPEchoServer-ForkN.c
- make TCPEchoServer-ForkN
- TCPEchoServer-ForkN の動作確認

動作確認方法：,,/01_TCPecho/TCPEchoClient をクライアントとして用いる。
(0)
  複数の端末（端末0,1,2... とする）を用意する。

(1)
  端末0 で TCPEchoServer-ForkN を実行する。
  子プロセスの個数（第2引数）は、あまり多くしないこと（2 or 3）
  コマンドはすぐに終了する。
  指定した個数の子プロセスが生成されたことを psコマンドで確認する。

(2)
  端末1,2... で、クライアントの実行する。

(3)
  何回かクライアントを実行する。
  処理する子プロセスの PID が変化することを確認する。
  子プロセスの個数を越えると、クライアントが待たされることを確認する。
  （サーバ動作を遅延するため sleep 関数を挿入する必要がある場合がある）

(4)
  サーバ（子プロセス）を停止する。
  ps コマンドで PID を確認して、1個ずつ kill コマンドで終了する。

## EOF
