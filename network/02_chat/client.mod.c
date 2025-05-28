/*********************************************/
/*       File name:  client.c                */
/*    Project name:  socket/1-1              */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

/*●●● 次の行 以降に必要なヘッダファイルを記述する． ●●●*/
# include <stdio.h>       /* printf()、fprintf()に必要 */
# include <sys/socket.h>  /* socket()、connect()、send()、recv()に必要 */
# include <arpa/inet.h>   /* sockaddr_in、inet_addr()に必要 */
# include <netdb.h>       /* gethostbyname() などに必要 */
# include <netinet/in.h>  /* sockaddr_in, htons などに必要 */
# include <sys/types.h>   /* socket(), connect() などに必要 */
# include <stdlib.h>      /* atoi()に必要 */
# include <string.h>      /* memset()に必要 */
# include <unistd.h>      /* close()に必要 */

/*●●● 次の行の〒の位置に，学籍番号から - を除いた値を用いて
         ポート番号を記述する． ●●●*/
#define PORT     (in_port_t)23437    /* サーバ(相手)のポート番号 */
#define BUF_LEN  512              /* 送受信のバッファの大きさ */


int  main(void)
{
  /* 変数宣言 */
  struct hostent  *server_ent;     /* サーバ(相手)の情報 */
  struct sockaddr_in  server;      /* サーバ(相手)のアドレス */
  int  soc;                        /* ソケットのディスクリプタ */
  char  hostname[] = "localhost";  /* サーバ(相手)のホスト名 */
  char  dbuf[BUF_LEN-10];              /* 送受信のバッファ  */
  char  buf[BUF_LEN];
  char  username[11];
  char input[8];
  int l;
  for(int i=0;i<11;i++) username[i]=0;
  for(int i=0;i<8;i++) input[i]=0;
  printf("your name(maxlength=8):\n");
  scanf("%s",input);  /* ソケットsoc から読む   */
  sprintf(username,"[%s]",input);
  for(l=0;username[l]!=0;l++);

  /* サーバ(相手)のホスト名からアドレス情報を得る  */
  if ((server_ent = gethostbyname(hostname)) == NULL) {
    perror("gethostbyname");
    exit(1);
  }

  /* サーバ(相手)のアドレスを sockaddr_in 構造体に格納  */
  memset((char *)&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  memcpy((char *)&server.sin_addr, server_ent->h_addr,
	 server_ent->h_length);

  /* IPv4でストリーム型のソケットを作成  */
  /*●●● socket() の引数を記述する． ●●●*/
  if ((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }

  /* サーバ(相手)に接続  */
  /*●●● connect() の引数を記述する． ●●●*/
  if (connect(soc, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("connect");
    exit(1);
  }

  /* 相手が先 */
  write(1, "Wait\n", 5);
 
  /* 通信のループ */
  do {
    int  n;                      /* 読み込まれたバイト数  */

    n = read(soc, buf, BUF_LEN);  /* ソケットsoc から読む   */
    printf("#reception:\n");
    write(1, buf, n);             /* 標準出力1 に書き出す   */
    if(strncmp(buf,"quit",4) == 0) break;

    printf("#send:\n");
    n = read(0, dbuf, BUF_LEN-10);    /* 標準入力0 から読む     */
    sprintf(buf,"%s%s",username,dbuf);
    if(strncmp(dbuf,"quit",4) == 0){
      write(soc, dbuf, n);
      break;
    }
    else write(soc, buf, n+l);           /* ソケットsoc に書き出す */
  } while(strncmp(buf, "quit" ,4) != 0);        /* 終了判定 */

  /* ソケットを閉じる */
  close(soc);

  return 0;
}
