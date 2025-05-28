/*********************************************/
/*       File name:  server.c                */
/*    Project name:  socket/1-1              */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

/*●●● 次の行 以降に必要なヘッダファイルを記述する． ●●●*/
# include <stdio.h>       /* printf()、fprintf()に必要 */
# include <sys/socket.h>  /* socket()、bind()、connect()に必要 */
# include <arpa/inet.h>   /* sockaddr_in、inet_ntoa()に必要 */
# include <stdlib.h>      /* atoi()に必要 */
# include <string.h>      /* memset()に必要 */
# include <unistd.h>      /* close()に必要 */

/*●●● 次の行の〒の位置に，学籍番号から - を除いた値を用いて
         ポート番号を記述する． ●●●*/
#define PORT     (in_port_t)23437    /* サーバ(自分)のポート番号 */
#define BUF_LEN  512              /* 送受信のバッファの大きさ */


int  main(void)
{
  /* 変数宣言 */
  struct sockaddr_in  me; /* サーバ(自分)の情報   */
  int  soc_waiting;       /* listenするソケット   */
  int  soc;               /* 送受信に使うソケット */
  char  buf[BUF_LEN];     /* 送受信のバッファ     */

  /* サーバ(自分)のアドレスを sockaddr_in 構造体に格納  */
  memset((char *)&me, 0, sizeof(me));
  me.sin_family = AF_INET;
  me.sin_addr.s_addr = htonl(INADDR_ANY);
  me.sin_port = htons(PORT);

  /* IPv4でストリーム型のソケットを作成  */
  /*●●● socket() の引数を記述する． ●●●*/
  if ((soc_waiting = socket( AF_INET, SOCK_STREAM, 0)) < 0 ) {
    perror("socket");
    exit(1);
  }

  /* サーバ(自分)のアドレスをソケットに設定 */
  /*●●● bind() の引数を記述する． ●●●*/
  if (bind(soc_waiting, (struct sockaddr *)&me, sizeof(me)) == -1) {
    perror("bind");
    exit(1);
  }

  /* ソケットで待ち受けることを設定 */
  /*●●● listen() の引数を記述する． ●●●*/
  listen( soc_waiting, 1);

  /* 接続要求が来るまでブロックする */
  /*●●● accept() の引数を記述する． ●●●*/
  soc = accept(soc_waiting, NULL, NULL);

  /* 接続待ちのためのソケットを閉じる */
  close(soc_waiting);

  /* こちらから先 */
  write(1, "Go ahead!\n", 10);

  /* 通信のループ */
  do {
    int  n;                       /* 読み込まれたバイト数  */

    printf("#send:\n");
    n = read(0, buf, BUF_LEN);    /* 標準入力0 から読む     */
    write(soc, buf, n);           /* ソケットsoc に書き出す */
    if(strncmp(buf,"quit",4) == 0) break;
    printf("#reception:\n");
    n = read(soc, buf, BUF_LEN);  /* ソケットsoc から読む   */
    write(1, buf, n);             /* 標準出力1 に書き出す   */
  } while (strncmp(buf,"quit",4) != 0);         /* 終了判定 */

  /* ソケットを閉じる */
  close(soc);

  return 0;
}
