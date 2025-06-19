07_multitask

----- ----- ----- ----- ----- 
課題0：演習準備

  ディレクトリ include と 07_multitask をコピーする。（コピー先に注意！）
する．

  07_multitask の中に以下のシンボリック リンクを作成する。
    ../01_TCPecho/DieWithError.c
    ../01_TCPecho/HandleTCPClient.c

----- ----- ----- ----- ----- 
課題1：Makefile の作成

  以下の仕様のMakefile を作成する。


環境変数 INCLUDE に以下をセットする。
    ../include

環境変数 CFLAGS に以下をセットする。
   -I$(INCLUDE)

環境変数 BIN に以下をセットする。
    fork
    TCPEchoServer-Fork

フォニー ターゲット all と clean を作成する。

依存関係：
fork ->
  fork.o
TCPEchoServer-Fork.o ->
  $(INCLUDE)/TCPEchoServer.h
TCPEchoServer-Fork ->
  AcceptTCPConnection.o
  CreateTCPServerSocket.o
  DieWithError.o HandleTCPClient.o
  TCPEchoServer-Fork.o

----- ----- ----- ----- ----- 
課題2：fork の実行
 - make fork
 - fork の動作確認

動作確認方法：
(0)
  2つの端末（端末0, 端末1 とする）を用意する。

(1)
  端末0 で fork を実行する。

(2)
  端末1 で fork が完全に終了するまで（親プロセスからのメッセージ表示が
表示されるまで）
    ps ux | grep defunct | grep -v grep
を何度も何度も実行する。
  ※ シェルのヒストリー機能（↑キー）を利用するとよい。
  ※ 動作確認を始める前に、予め、1回実行しておくとよい。

  1. fork を実行してから最初の3秒（子プロセスが終了するまで）はゾンビが存在
しないことを確認する。
  2. 子プロセスが終了したらゾンビが発生することを確認する。
  3. 親プロセスがゾンビを回収してゾンビが存在しなくなることを確認する。

----- ----- ----- ----- ----- 
課題3： TCPEchoServer-Fork の完成
 - ソースコードファイルの穴埋め
    AcceptTCPConnection.c
    CreateTCPServerSocket.c
    TCPEchoServer-Fork.c
      * まず、sleep をコメントアウトしているまま
      * 次に、sleep のコメントを外して
 - make TCPEchoServer-Fork
 - TCPEchoServer-Fork の動作確認

動作確認方法：../01_TCPecho/TCPEchoClient をクライアントとして用いる。
(0)
  2つの端末（端末0，端末1 とする）を用意する。

(1)
  端末0 で TCPEchoServer を実行する。

(2)
  端末1 で、クライアントの実行 と 上記のps|grep|grepコマンド を
  複数回実行し、
   - childProcCount の数が変化する様子を確認する。
   - ゾンビの PID が変化していく様子を確認する。

## EOF
