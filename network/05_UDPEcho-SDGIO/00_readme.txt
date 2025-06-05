05_UDPechoSIGIO

----- ----- ----- ----- ----- 
課題0：演習準備

前回と同じく、01_TCPecho にある DieWithError.c へのシンボリック リンクを
作成しておく。

----- ----- ----- ----- ----- 
課題1：Makefile の作成

 以下の仕様のMakefile を作成する。

環境変数 BIN に以下をセットする。
  SigAction
  SigAction.mod
  UDPEchoServer-SIGIO

フォニー ターゲット all と clean を作成する。

依存関係：	
SigAction -> DieWithError.o SigAction.o

SigAction.mod -> DieWithError.o SigAction.mod.o

UDPEchoServer-SIGIO -> DieWithError.o UDPEchoServer-SIGIO.o


----- ----- ----- ----- ----- 
課題2：SigAction の完成

Ctrl-C を入力すると、
Interrupt Received.  Exiting program.
と表示し終了する。

- SigAction.c の穴埋め
- make SigAction
- SigAction の実行&動作確認

----- ----- ----- ----- ----- 
課題3：SigAction.mod の作成

Ctrl-C を入力すると、
Interrupt Received.
と表示し、実行を続ける。
SigAction.mod は無限ループするプログラムである。

- SigAction.c を SigAction.mod.c にコピーする。
- SigAction.mod.c の InterruptSignalHandler 関数を修正する。	
- make SigAction.mod
- SigAction.mod の実行&動作確認
- SigAction.mod の終了
  * ps a コマンドでプロセス番号を調べる
  * kill コマンドでプロセスを強制終了させる。

----- ----- ----- ----- ----- 
課題4：UDPechoServer-SIGIO の完成

04_UDPecho の UDPechoClient と通信しながら、
3秒ごとに . を表示する。
UDPechoServer-SIGIO は無限ループするプログラムである。

- UDPechoServer-SIGIO.c の穴埋め
- make UDPechoServer-SIGIO
- UDPechoServer-SIGIO の動作確認
  * UDPechoServer-SIGIO を実行
  * UDPechoClient を(別の端末で)実行
- UDPechoServer-SIGIO の終了
  * ps a コマンドでプロセス番号を調べる
  * kill コマンドでプロセスを強制終了させる。

----- ----- ----- ----- ----- 
課題5：課題成果の提出

シェルスクリプト archive.sh を実行して作成される
ファイル 05_UDPechoSIGIO.tar.gz.b64 を提出する。

## EOF
