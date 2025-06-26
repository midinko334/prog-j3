#include "TCPEchoServer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

void  ProcessMain(int  servSock);     /* プロセスのメインプログラム */


/*●●● main() の引数 ●●●*/
int  main(int argc, char *argv[])
{
  int  servSock;                  /* サーバのソケットディスクリプタ */
  unsigned short  echoServPort;   /* サーバのポート */
  pid_t  processID;               /* プロセスID */
  unsigned int  processLimit;      /* 作成する子プロセスの数 */
  unsigned int  processCt;         /* プロセスのカウンタ */

  /*●●● 引数チェック ●●●*/
  if (argc != 3) {  /* 引数の個数が正しいか確認 */
    /*●●● fprintf() の引数 ●●●*/
    fprintf (stderr, "Usage: %s <Server Port> <Fork Count>\n", argv[0]);
    exit(1);
  }

  /*●●● 右辺 ●●●*/
  echoServPort = atoi(argv[1]);  /* 1つ目の引数： ローカルポート */

  /*●●● 右辺 ●●●*/
  processLimit = atoi(argv[2]);  /* 2つ目の引数： 子プロセスの個数 */

  /*●●● CreateTCPServerSocket() の引数 ●●●*/
  servSock = CreateTCPServerSocket(echoServPort);

  for (processCt = 0;  processCt < processLimit;  processCt++) {
    /* 子プロセスのフォークとエラーの報告 */
    /*●●● 右辺 ●●●*/
    processID = fork();

    /*●●● 分岐条件（else if の方も） ●●●*/
    if (processID < 0) {
      DieWithError("fork() failed");
    } else if (processID == 0) {  /* 子プロセスの場合 */
      ProcessMain(servSock);
    }
  }

  exit(0);  /* 子プロセスの処理を続行 */
}


void ProcessMain(int servSock)
{
  int  clntSock;  /* クライアントが接続するソケットディスクリプタ */

  for ( ; ; ) { /* 処理を繰り返し */
    /*●●● AcceptTCPConnection() の引数 ●●●*/
    clntSock = AcceptTCPConnection(servSock);

    /*●●● printf() の引数 ●●●*/
    printf("Handling client with child process: %d\n", (int) getpid());

    /*●●● HandleTCPClient() の引数 ●●●*/
    HandleTCPClient(clntSock);

//    sleep(3);
  }
}
