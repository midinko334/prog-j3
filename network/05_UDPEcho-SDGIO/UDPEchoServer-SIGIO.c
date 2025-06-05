/*●●● 必要なヘッダファイルを列挙する ●●●*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#define ECHOMAX 255    /* エコー文字列の最大長 */

void  DieWithError(char  *errorMessage);  /* エラー処理関数 */
void  UseIdleTime();                      /* アイドル時間を利用する関数 */
void  SIGIOHandler(int  signalType);      /* SIGIOのハンドラ関数 */

int  sock;  /* ソケット（シグナルハンドラ用にグローバルに作成） */


int  main(int argc, char *argv[])
{
  struct sockaddr_in  echoServAddr;  /* サーバのアドレス */
  unsigned short  echoServPort;      /* サーバのポート番号 */
  struct sigaction  handler;         /* シグナル処理のアクションを定義 */
  int ret_bind;        /*●●● 型名を記述 ●●●*/
  int ret_sigfillset;  /*●●● 型名を記述 ●●●*/
  int ret_sigaction;   /*●●● 型名を記述 ●●●*/
  int ret_fcntl;       /*●●● 型名を記述 ●●●*/

  /* パラメータの個数が正しいか確認 */
  /*●●● 分岐条件 ●●●*/
  if (argc != 2) {
    /*●●● fprintf() の引数 ●●●*/
    fprintf(stderr, "Usage: %s <UDP SERVER PORT>\n", argv[0]);
    exit(1);
  }

  /*●●● 右辺 ●●●*/
  echoServPort = atoi(argv[1]);  /* 第1引数： ローカルポート番号 */

  /* データグラムの送受信に使うソケットを作成 */
  /*●●● socket() の引数 ●●●*/
  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock < 0) {
    DieWithError("socket() failed");
  }

  /* サーバのアドレス構造体をセットアップ */
  /*●●● memset() の引数 ●●●*/
  memset(&echoServAddr, 0, sizeof(echoServAddr));    /* 構造体にゼロを埋める */

  /*●●● 右辺 ●●●*/
  echoServAddr.sin_family = AF_INET;                 /* インターネットファミリ */

  /*●●● htonl() の引数 ●●●*/
  echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* 任意の受信インタフェース */

  /*●●● htons() の引数 ●●●*/
  echoServAddr.sin_port = htons(echoServPort);       /* ポート */

  /* ローカルアドレスへバインド */
  /*●●● bind() の引数 ●●●*/
  ret_bind = bind(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr));
  if (ret_bind < 0) {
    DieWithError("bind() failed");
  }

  /* SIGIOのシグナルハンドラを設定 */
  /*●●● 右辺 ●●●*/
  handler.sa_handler = SIGIOHandler;

  /* 全シグナルをマスクするマスクを作成 */
  /*●●● sigfillset() の引数 ●●●*/
  ret_sigfillset = sigfillset(&handler.sa_mask);
  if (ret_sigfillset < 0) {
    DieWithError("sigfillset() failed");
  }

  /* フラグなし */
  handler.sa_flags = 0;

  /*●●● sigaction() の引数 ●●●*/
  ret_sigaction = sigaction(SIGIO, &handler, 0);
  if (ret_sigaction < 0) {
    DieWithError("sigaction() failed for SIGIO");
  }

  /* ソケットを所有してSIGIOメッセージを受信させる */
  /*●●● fcntl() の引数 ●●●*/
  ret_fcntl = fcntl(sock, F_SETOWN, getpid());
  if (ret_fcntl < 0) {
    DieWithError("Unable to set process owner to us");
  }

  /* ノンブロッキングI/OとSIGIO送信をセットアップ */
  /*●●● fcntl() の引数 ●●●*/
  ret_fcntl = fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC);
  if (ret_fcntl < 0) {
    DieWithError("Unable to put client sock into nonblocking/async mode");
  }

  /* 処理を離れてほかの仕事をする（エコーはバックグラウンドで発生する） */

  for ( ; ; ) {
    UseIdleTime();
  }

  /* この部分には到達しない */
}


void  UseIdleTime()
{
  /*●●● 作業内容を記述する ●●●*/
  printf(".\n");
  sleep(3);
}


void  SIGIOHandler(int  signalType)
{
  struct sockaddr_in  echoClntAddr; /* データグラムの送信元アドレス */
  unsigned int  clntLen;            /* アドレス長 */
  int  recvMsgSize;                 /* データグラムのサイズ */
  char  echoBuffer[ECHOMAX ];       /* データグラムのバッファ */
  int ret_sendto;  /*●●● 型名を記述 ●●●*/

  do {  /* 入力データがなくなるまで実行 */
    /* 入出力パラメータのサイズを設定 */
    /*●●● 右辺 ●●●*/
    clntLen = sizeof(echoClntAddr);

    /*●●● recvfrom() の引数 ●●●*/
    recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr *)&echoClntAddr, &clntLen);
    if (recvMsgSize < 0) {
      /* recvfrom()がブロックしようとした場合（許容される唯一のエラー） */
      if (errno != EWOULDBLOCK) {
	DieWithError("recvfrom() failed");
      }
    } else {
      printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

      /*●●● sendto() の引数 ●●●*/
      ret_sendto = sendto(sock, echoBuffer, recvMsgSize, 0, (struct sockaddr *)&echoClntAddr, clntLen);
      if (ret_sendto != recvMsgSize) {
	DieWithError("sendto() failed");
      }
    }
  } while (recvMsgSize >= 0);

  /* すべての受信が完了 */
}
