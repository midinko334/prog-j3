/*********************************************/
/*       File name:  server.c                */
/*    Project name:  socket/3moku            */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

/* 3目並べの後手(サーバ)プログラム */

#include "goban.h"

int  main(void)
{
  int  soc;                /* ソケットのディスクリプタ */
  char  my_stone   = 'o';  /* 自分の石                 */
  char  peer_stone = 'x';  /* 相手の石                 */
  int  iportno;      /* 後手(サーバ)のport */
  char  dum;	/* scanfの改行消す */
  in_port_t  portno;	 /* 後手(サーバ)のport */

  printf("Input server's Port: ");
  scanf("%d%c",&iportno,&dum);
  portno=(in_port_t)iportno;

  /* 接続受付完了まで */
  soc = setup_server(portno);
  if (soc == -1) {
    exit(1);
  }

  /* 碁盤の初期化 */
  goban_init(soc, my_stone, peer_stone);

  /* ループ */
  while (1) {
    /* 相手の番 */
    goban_show();
    printf("Wait.\n");
    if (goban_peer_turn() == -1) {
      break;
    }

    /* 自分の番 */
    goban_show();
    printf("Go ahead.\n");
    if (goban_my_turn() == -1) {
      break;
    }
  }

  /* 終了処理 */
  goban_destroy();

  return 0;
}
