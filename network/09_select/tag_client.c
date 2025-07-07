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


int  main(void)
{
  int  soc;  /* ソケットのディスクリプタ */
  char  hostname[HOSTNAME_LENGTH];  /* サーバ(相手)のホスト名 */

  /* サーバのホスト名の入力 */
  printf("Input server's hostname: ");
  fgets(hostname, HOSTNAME_LENGTH, stdin);
  chop_newline(hostname, HOSTNAME_LENGTH);

  /* 接続まで */
  soc = setup_client(hostname, PORT);
  if (soc == -1) {
    exit(1);
  }

  /* セッションモジュールの初期化 */
  session_init(soc, 'x', 10, 10, 'o', 1, 1);

  /* セッションのループ */
  session_loop();

  return 0;
}
