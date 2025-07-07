/*********************************************/
/*       File name:  tag_client.c            */
/*    Project name:  socket/tag              */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

/* 鬼ごっこゲームのクライアントプログラム */

#include "tag_session.h"
#include "tag.h"
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

int  main(int argc,char *argv[])
{
  int  soc;  /* ソケットのディスクリプタ */

  /* 接続まで */
  if (argc -1 != 1) {
    fprintf(stderr, "Usage: %s <Server_Port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  soc = setup_client(argv[1],PORT);

  /* セッションモジュールの初期化 */
  session_init(soc, 'o', 1, 1, 'x', 10, 10);

  /* セッションのループ */
  session_loop();

  return 0;
}
