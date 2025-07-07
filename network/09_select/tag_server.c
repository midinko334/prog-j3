/*********************************************/
/*       File name:  tag_server.c            */
/*    Project name:  socket/tag              */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

/* 鬼ごっこゲームのサーバプログラム */

#include "tag_session.h"
#include "tag.h"
#include <stdlib.h>


int  main(void)
{
  int soc;   /* ソケットのディスクリプタ */

  /* 接続受付まで */
  soc = setup_server(PORT);
  if (soc == -1) {
    exit(1);
  }

  /* セッションモジュールの初期化 */
  session_init(soc, 'o', 1, 1, 'x', 10, 10);

  /* セッションのループ */
  session_loop();

  return 0;
}
