06_timeout

----- ----- ----- ----- ----- 
課題0：演習準備

　前回までと同じく、01_TCPecho にある DieWithError.c への
  シンボリックリンクを作成しておく。

  05_UDPechoSIGIO/UDPEchoServer-SIGIO を準備する。

----- ----- ----- ----- ----- 
課題1：Makefile の作成

  以下の仕様のMakefile を作成する。

  環境変数 BIN に以下をセットする。
    UDPEchoClient-Timeout

  フォニー ターゲット all と clean を作成する。

依存関係：
UDPEchoClient-Timeout -> UDPEchoClient-Timeout.o DieWithError.o

----- ----- ----- ----- ----- 
課題2：UDPEchoClient-Timeout の完成
  - UDPEchoClient-Timeout.c の穴埋め
  - make UDPEchoClient-Timeout
  - UDPEchoClient-Timeout 動作確認

動作確認方法：../05_UDPechoSIGIO/UDPEchoServer-SIGIO をサーバとして用いる。
(0)
  2つの端末（端末0，端末1 とする）を用意する。

(1)
  サーバを起動する前に、端末0 にて いきなり UDPEchoClient-Timeout を実行
してみる。
  サーバが起動していないので再接続を試みるが、5秒経過したら諦めて終了する。

(2)
  もう一度 UDPEchoClient-Timeout を実行してみる。
  その後，5秒以内（※）に，端末1 で 05_UDPechoSIGIO/UDPEchoServer-SIGIO を
実行する。予め、端末1 で Enter を押せばサーバを実行できるように準備して
おくとよい。
  UDPEchoClient-Timeout が無事にサーバに接続してエコーバックされた文字列が
表示されることを確認する。

※ 実際には、もう少し早くしないと、UDPEechoClient-Timeout がタイムアウトし
　 てしまう。

(3)
  サーバを実行した状態で、UDPEchoClient-Timeout を実行してみる。
  クライアントは すぐに接続でき、きちんとエコーバックされることを確認
  する。

(4)
  サーバを C-c で終了する。
  
## EOF
