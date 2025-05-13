/*********************************************/
/*       File name:  setup_client.c          */
/*    Project name:  socket/mylib            */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

#include "mylib.h"

int  setup_client(char *hostname,
		  in_port_t port)
  /* 戻り値   ソケットのディスクリプタ */
  /* hostname 接続先のホスト名         */
  /* port     接続先のポート番号       */
{
  /* 変数の宣言 */
  struct hostent  *server_ent; /* 接続先のホストの情報       */
  struct sockaddr_in  server;  /* 接続先のソケットのアドレス */
  int  soc;                    /* 通信に使うソケット         */

  /* 接続先のホスト名からホストの情報を得る */
  if ((server_ent = gethostbyname(hostname)) == NULL) {
    perror("gethostbyname");
    return -1;
  }

  /* 接続先のアドレスを sockaddr_in 構造体に設定 */
  memset((char *)&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  memcpy((char *)&server.sin_addr, server_ent->h_addr,
	 server_ent->h_length);

  /* IPv4 でストリーム型のソケットを作成 */
  soc = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (soc < 0) {
    perror("socket");
    return -1;
  }

  /* 接続 */
  if (connect(soc, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("connect");
    return -1;
  }
  fprintf(stderr, "connected.\n");

  /* ソケットを返す */
  return soc;
}
