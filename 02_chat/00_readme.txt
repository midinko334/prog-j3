TCPを利用したチャット

課題1
サンプルプログラム server と client の完成
・Makefile の作成と make all の実行
　コンパイルエラーするので...
・server.c と client.c の修正
《server と client の正しい挙動》
  1. 端末Ｓでserver を起動する。
　2. 端末Ｃで client を起動する。
　3. 端末Ｓから文字列を入力すると、端末Ｃに表示される。
　4. 端末Ｃから文字列を入力すると、端末Ｓに表示される。
　5. 3. と4. を交互に繰り返す。
  6. 端末Ｃから文字列 quit を入力すると、client も server も終了する。

課題2
server と client の改良 ＝ server.mod と client.mod の作成
・server.c, clent.c をそれぞれ server.mod.c と client.mod.c にコピー
・Makefile の修正
・server.mod.c と client.mod.c の修正とmake all の実行
《改良点》
・どちらから入力した文字列なのか、どちらが送信する番なのか、
　分かりにくいので、適切なプロンプトを表示する。
・server 側から文字列 quit を送信しても server も client も終了する。

課題3
・make clean を実行し、オブジェクトファイルと実行可能ファイルが
　すべて消去されたことを確認する。
・make all を実行し、error message や warning が表示されないことを
　確認する。
・./archive.sh を実行して、提出用ファイル 02_chat.tar.gz.b64 を作成する。
　提出用ファイルには、Makefile, server.c, client.c, server.mod.c client.mod.c
　が含まれる。
・02_chat.tar.gz.b64 を提出してください。

以　上
