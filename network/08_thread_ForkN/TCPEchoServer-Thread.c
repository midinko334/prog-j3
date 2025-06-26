/*●●● 必要なヘッダファイルを列挙する ●●●*/
#include "TCPEchoServer.h"  /* TCPエコーサーバのヘッダファイルをインクルード */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

void  *ThreadMain(void  *arg);  /* スレッドのメインプログラム */


/* クライアントスレッドに渡す引数の構造体 */
/*●●● 必要なメンバを列挙する ●●●*/
struct ThreadArgs {
  int clntSock;
};


/*●●● main() の引数 ●●●*/
int  main(int argc, char *argv[])
{
  int  servSock;  /* サーバのソケットディスクリプタ */
  int  clntSock;  /* クライアントのソケットディスクリプタ */
  unsigned short  echoServPort;     /* サーバのポート */
  pthread_t  threadID;              /* pthread_create()が返すスレッドID */
  struct ThreadArgs  *threadArgs;   /* スレッドの引数構造体へのポインタ */
  int ret_pc;  /*●●● 変数の型 ●●●*/

  /*●●● 引数チェック ●●●*/
  if (argc != 2) {  /* 引数の個数が正しいか確認 */
    /*●●● fprintf() の引数 ●●●*/
    fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
    exit(1);
  }

  /*●●● 右辺 ●●●*/
  echoServPort = atoi(argv[1]);  /* 1つ目の引数： ローカルポート */

  /*●●● CreateTCPServerSocket() の引数 ●●●*/
  servSock = CreateTCPServerSocket(echoServPort);

  for ( ; ; ) {  /* プログラムが終了するまで繰り返し実行 */
    /*●●● AcceptTCPConnection() の引数 ●●●*/
    clntSock = AcceptTCPConnection(servSock);

    /* クライアント引数用にメモリを新しく確保 */
    /*●●● 右辺 ●●●*/
    threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs));

    /*●●● 分岐条件 ●●●*/
    if (threadArgs == NULL) {
      DieWithError("malloc() failed");
    }
    /*●●● 左辺 ●●●*/
    threadArgs->clntSock = clntSock;

    /* クライアントスレッドを生成 */
    /*●●● pthread_create() の引数 ●●●*/
    ret_pc = pthread_create(&threadID, NULL, ThreadMain, (void *) threadArgs);
    if (ret_pc != 0) {
      DieWithError("pthread_create() failed");
    }
    printf("with thread %ld\n", (long int) threadID);
//    sleep(3);
  }

  /* この部分には到達しない */
}

void  *ThreadMain(void  *threadArgs)
{
  int  clntSock;  /* クライアント接続用ソケットディスクリプタ */

  /* 戻り時に、スレッドのリソースを割り当て解除 */
  /*●●● pthread_detach() の引数 ●●●*/
  pthread_detach(pthread_self());

  /* ソケットのファイルディスクリプタを引数から取り出す */
  /*●●● 右辺 ●●●*/
  clntSock = ((struct ThreadArgs *) threadArgs)->clntSock;

  /*●●● free() の引数 ●●●*/
  free(threadArgs);  /* 引数に割り当てられていたメモリを解放 */

  /*●●● HandleTCPClient() の引数 ●●●*/
  HandleTCPClient(clntSock);

  return (NULL);
}
