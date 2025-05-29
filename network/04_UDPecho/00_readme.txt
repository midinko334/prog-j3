04_UDPecho

----- ----- ----- ----- ----- 
課題0：演習準備

ディレクトリ /home/class/j3/network/04_UDPecho をコピーする。
コピー先のディレクトリは、ディレクトリ 01_TCPecho と同じレベルに作成する。

ワーキングディレクトリ 04_UDPecho に cd して、
01_TCPecho にある DieWithError.c へのシンボリック リンクを作成する。
    $ ln -s ../01_TCPecho/DieWithError.c .

----- ----- ----- ----- ----- 
課題1：Makefile の作成

以下の仕様のMakefile を作成する。

環境変数 BIN に、作成する実行可能ファイルをセットする。
  UDPEchoClient
  UDPEchoServer

フォニー ターゲット all と clean を作成する。

依存関係：
UDPEchoClient -> DieWithError.o UDPEchoClient.o

UDPEchoServer -> DieWithError.o UDPEchoServer.o

----- ----- ----- ----- ----- 
課題2：プログラムの完成（i.e. 穴埋め & make & 実行）

UDPEchoClient.c
UDPEchoServer.c

----- ----- ----- ----- ----- 
課題3：課題成果の提出

シェルスクリプト archive.sh を実行して作成される 
ファイル 04_UDPecho.tar.gz.b64 を提出する。

## EOF
