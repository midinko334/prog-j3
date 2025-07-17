/*********************************************/
/*       File name:  server.c                */
/*    Project name:  socket/mtalk            */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

/* ミニ電子会議サーバプログラム */

#include <stdio.h>
#include "sessionman.h"
#include "mylib.h"

#include <stdlib.h>


int main(int  argc,  char  *argv[])
	/* argc -1  1 であって欲しい */
	/* argv[1]  参加者人数      */
{
  int  num;   /* 参加者人数           */
  int  soc;   /* 待ち受けソケット     */
  int  maxfd; /* 最大のディスクリプタ */

  /*●●● main() の引数の処理を記述する ●●●*/
  if (argc != 2) {
    fprintf(stderr, "Usage: %s number_of_attendants\n", argv[0]);
    exit(1);
  }

  /* 引数で参加者人数を知る。 */
  /*●●● 右辺 ●●●*/
  num = atoi(argv[1]);
  if (num <= 0  ||  num > MAX_ATTENDANTS) {
    fprintf(stderr, "attendants limit= %d\n", MAX_ATTENDANTS);
    exit(2);
  }

  /* ソケットのディスクリプタを soc に受け取る */
  soc = mserver_socket(PORT, num);
  if (soc == -1) {
    fprintf(stderr, "cannot setup server\n");
    exit(3);
  }

  /* m_accept にコールバック関数の enter を渡す。
     返って来るのは最大のディスクリプタ */
  maxfd = mserver_maccept(soc, num, enter);

  /* セッションモジュールの初期化 */
  sessionman_init(num, maxfd);

  /* セッション管理のメインループ */
  sessionman_loop();

  return 0;
}
