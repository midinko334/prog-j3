/*********************************************/
/*       File name:  setup_mserver,c         */
/*    Project name:  socket/mylib            */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*********************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h>
#include <string.h>


int mserver_socket(in_port_t port, int backlog)
	/* 戻り値   待ち受けソケットのディスクリプタ */
	/* port     接続先のポート番号               */
	/* backlog  待ち受けの数                     */
{
  /* 変数の宣言 */
  struct sockaddr_in me; /* 自分のソケットのアドレス         */
  int soc_waiting;       /* 待ち受けソケットのディスクリプタ */

  /* 自分のアドレスを sockaddr_in 構造体に設定 */
  memset((char *)&me, 0, sizeof(me));
  me.sin_family = AF_INET;
  me.sin_addr.s_addr = htonl(INADDR_ANY);
  me.sin_port = htons(port);

  /* IPv4 でストリーム型のソケットの作成 */
  if ((soc_waiting = socket(AF_INET,SOCK_STREAM,0)) < 0) {
    perror("socket");
    return -1;
  }

  //# 追加
  //# https://freebsd.sing.ne.jp/lang/c/14.html
  int yes = 1;
  if (setsockopt(soc_waiting, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes,
                 sizeof(yes)) < 0) {
    perror("ERROR on setsockopt");
    return 2;
  }

  /* ソケットに自分のアドレスを設定 */
  if (bind(soc_waiting,(struct sockaddr *)&me,sizeof(me)) == -1) {
    perror("bind");
    return -1;
  }

  /* ソケットで接続待ちの設定 */
  if (listen(soc_waiting, backlog) == -1) {
    perror("listen");
    return -1;
  }
  fprintf(stderr,"successfully setup, now waiting.\n");

  /* 待ち受け用のディスクリプタを返す */
  return soc_waiting;
}

/*  マルチアクセプト  */
int mserver_maccept(int soc_waiting, int limit, void (*func)() )
	/* 戻り値   最大のソケットのディスクリプタ      */
	/* soc_waiting   待ち受けに使うソケット         */
	/* limit    accept の上限                       */
	/* func     accept 毎に実行する関数へのポインタ */
{
  int i;   /* ループカウンタ */
  int fd;  /* ディスクリプタを入れる作業用変数 */

  /* accept を limit 回数実行 */
  for (i = 0;  i < limit ; i++) {
    if ((fd = accept(soc_waiting, NULL, NULL)) == -1) {
      fprintf(stderr, "accept error\n");
      return -1;
    }
    (*func)(i, fd);
  }
  
  /* 待ち受けのソケットを閉じる */
  close(soc_waiting);

  /* 最後の fd つまり最大値を返す */
  return fd;
}
