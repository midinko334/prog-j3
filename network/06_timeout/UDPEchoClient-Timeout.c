/*●●● 必要なヘッダファイルを列挙する ●●●*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>

#define ECHOMAX        255    /* エコー文字列の最大長 */
#define TIMEOUT_SECS   2      /* 再送信までの秒数 */
#define MAXTRIES       5      /* 最大試行回数 */

/* 送信回数のカウンタ（シグナルハンドラからのアクセス用、グローバル） */
int  tries = 0;

void  DieWithError(char *errorMessage);   /* エラー処理関数 */
void  CatchAlarm(int ignored);            /* SIGALRMのハンドラ */


int  main(int  argc, char  *argv[])
{
  int  sock;                         /* ソケットディスクリプタ */
  struct sockaddr_in  echoServAddr;  /* エコーサーバのアドレス */
  struct sockaddr_in  fromAddr;      /* エコー送信元のアドレス */
  unsigned short  echoServPort;      /* エコーサーバのポート番号 */
  unsigned int  fromSize;            /* recvfrom()のアドレスの入出力サイズ */
  struct sigaction  myAction;        /* シグナルハンドラの設定用 */
  char  *servIP;                     /* サーバのIPアドレス */
  char  *echoString;                 /* エコーサーバへ送信する文字列 */
  char  echoBuffer[ECHOMAX+1];       /* エコー文字列の受信バッファ */
  int  echoStringLen;                /* エコー文字列の長さ */
  int  respStringLen;                /* 受信データグラムの長さ */
  int ret_sigfillset;  /*●●● 型名 ●●●*/
  ssize_t ret_sendto;  /*●●● 型名 ●●●*/
   
  if ((argc -1 < 2) || (argc -1 > 3)) {  /* 引数の個数が正しいか確認 */
    fprintf(stderr,
	    "Usage: %s <Server_IP> <Echo_Word> [<Echo_Port>]\n", 
	    argv[0]);
    exit(1);
  }

  /* 1つ目の引数： サーバのIPアドレス（ドット区切り10進表記） */
  /*●●● 右辺 ●●●*/
  servIP = argv[1];

  /* 2つ目の引数： エコー文字列 */
  /*●●● 右辺 ●●●*/
  echoString = argv[2];

  /*●●● 右辺 ●●●*/
  echoStringLen = strlen(echoString);
  if (echoStringLen > ECHOMAX) {
    DieWithError("Echo word too long");
  }
   
  if (argc -1 == 3) {
    /*●●● 右辺 ●●●*/
    echoServPort = atoi(argv[3]); /* 指定のポート番号があれば使用 */
  } else {
    /*●●● 右辺 ●●●*/
    echoServPort = 7; /* エコーサービスのwell-known番号 */
  }
   
  /* ベストエフォート型UDPデータグラムソケットを作成 */
  /*●●● socket() の引数 ●●●*/
  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock < 0) {
    DieWithError("socket() failed");
  }
   
  /* アラームシグナル用シグナルハンドラのセット */
  /*●●● 右辺 ●●●*/
  myAction.sa_handler = CatchAlarm;

  /* ハンドラ内ではすべてをブロック */
  /*●●● sigfillset() の引数 ●●●*/
  ret_sigfillset = sigfillset(&myAction.sa_mask);
  if (ret_sigfillset < 0) {
    DieWithError("sigfillset() failed");
  }
  myAction.sa_flags = 0;

  /*●●● sigaction() の引数 ●●●*/
  ret_sigfillset = sigaction(SIGALRM, &myAction, 0);
  if (ret_sigfillset < 0) {
    DieWithError("sigaction() failed for SIGALRM");
  }
   
  /* サーバのアドレス構造体を作成 */
  memset(&echoServAddr, 0, sizeof(echoServAddr));  /* 構造体をゼロで埋める */

  echoServAddr.sin_family = AF_INET;
  echoServAddr.sin_addr.s_addr = inet_addr(servIP); /* サーバのIPアドレス */
  echoServAddr.sin_port = htons(echoServPort);       /* サーバのポート番号 */
   
  /* 文字列をサーバに送信 */
  ret_sendto = sendto(sock, echoString, echoStringLen, 0, 
		      (struct sockaddr *) &echoServAddr,
		      sizeof(echoServAddr));
  /*●●● if 文の条件 ●●●*/
  if (ret_sendto != echoStringLen) {
    DieWithError("sendto() sent a different number of bytes than expected");
  }

  /* 応答を受信 */
  fromSize = sizeof(fromAddr);
  /*●●● alarm() の引数 ●●●*/
  alarm(TIMEOUT_SECS);  /* タイムアウト時間を設定 */
  while ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0,
				   (struct sockaddr *) &fromAddr, 
				   &fromSize)) < 0) {
    if (errno == EINTR) {  /* アラームの終了 */
      if (tries < MAXTRIES) {  /* triesはシグナルハンドラ内でインクリメント */
	printf("timed out, %d more tries...\n", MAXTRIES-tries);
	ret_sendto = sendto(sock, echoString, echoStringLen, 0, 
			    (struct sockaddr *) &echoServAddr, 
			    sizeof(echoServAddr));
	if (ret_sendto != echoStringLen) {
	  DieWithError("sendto() failed");
	}
	/*●●● alarm() の引数 ●●●*/
	alarm(TIMEOUT_SECS);
      } else {
	DieWithError("No Response");
      }
    } else {
      DieWithError("recvfrom() failed");
    }
  }
   
  /* recvfrom() が何かを受信したら、タイムアウトをキャンセル */
  /*●●● alarm() の引数 ●●●*/
  alarm(0);
   
  /* 受信データをNULL文字で終端させる */
  /*●●● 右辺 ●●●*/
  echoBuffer[respStringLen] = '\0';
  printf("Received: %s\n", echoBuffer);  /* 受信データを表示 */
    
  close(sock);

  return 0;
}

void  CatchAlarm(int  ignored)  /* SIGALRMのハンドラ */
{
  /*●●● increment 処理 ●●●*/
  tries ++;
}
