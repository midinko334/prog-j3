/*********************************************/
/*       File name:  client.c                */
/*    Project name:  socket/mtalk            */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

/* ミニ電子会議クライアントプログラム */

#include "session.h"

#include <stdlib.h>
#include "mylib.h"

int  main(void)
{
  int   soc;                        /* ソケット */
  char  hostname[HOSTNAME_LENGTH];  /* サーバのホスト名 */

  /* サーバのホスト名の入力 */
  printf("input server's hostname = ");
  fgets(hostname, HOSTNAME_LENGTH, stdin);
  chop_newline(hostname, HOSTNAME_LENGTH);

  /* クライアントとしてのセットアップ */
  soc = setup_client(hostname, PORT);
  if (soc == -1) {
    exit(1);
  }

  /* セッションモジュールの初期化 */
  session_init(soc);

  /* セッションのメインループ */
  session_loop();

  return 0;
}
