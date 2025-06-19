/*●●● 必要なヘッダファイルを列挙する ●●●*/
#include "TCPEcho.h"  /* TCPエコーサーバのヘッダファイルをインクルード */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int  main(int  argc, char  *argv[])
{
  int  servSock;                     /* サーバのソケットディスクリプタ */
  int  clntSock;                     /* クライアントのソケットディスクリプタ */
  unsigned short  echoServPort;      /* サーバのポート番号 */
  pid_t  processID;                  /* fork()が返すプロセスID */
  unsigned int  childProcCount = 0;  /* 子プロセスの個数 */

  /* 引数の個数が正しいか確認 */
  if (argc -1 != 1) {
    fprintf(stderr, "Usage: %s <Server_Port>\n", argv[0]);
    exit(1);
  }

  /*●●● 右辺 ●●●*/
  echoServPort = atoi(argv[1]);  /* 1つ目の引数： ローカルポート */

  /*●●● CreateTCPServerSocket() の引数 ●●●*/
  servSock = CreateTCPServerSocket(echoServPort);

  for ( ; ; ) {  /* 処理を繰り返し実行 */
    /*●●● AcceptTCPConnection() の引数 ●●●*/
    clntSock = AcceptTCPConnection(servSock);

    /* 子プロセスのフォークとエラーを報告 */
    /*●●● 右辺 ●●●*/
    processID = fork();
    if (processID < 0) {
      DieWithError("fork() failed");
    } else if (processID == 0) {  /* 子プロセスの場合 */
      /*●●● close() の引数 ●●●*/
      close(servSock);  /* 待ち受け中のソケットを子プロセスがクローズ */

      /*●●● HandleTCPClient() の引数 ●●●*/
      HandleTCPClient(clntSock);

      exit(0);  /* 子プロセスを終了 */
    }

    printf("with child process: %d\n", (int) processID);
    /*●●● close() の引数 ●●●*/
    close(clntSock);  /* 子のソケットディスクリプタを親がクローズ */
    childProcCount ++;  /* 未回収の子プロセスの個数をインクリメント */

    printf("1: childProcCount = %d \n", childProcCount);
    /* sleep(1); */

    while (childProcCount) {  /* 全ゾンビをクリーンアップ */
      /* ノンブロッキングで実行 */
      /*●●● waitpid() の引数 ●●●*/
      processID = waitpid(-1, NULL, WNOHANG);
      if (processID < 0) {  /* waitpid()のエラーを確認 */
	DieWithError("waitpid() failed");
      } else if (processID == 0) {  /* ゾンビが存在しない */
	break;
      } else {
	childProcCount --;  /* 子プロセスを回収 */
      }
    }

    printf("2: childProcCount = %d \n", childProcCount);
  }
  /* この部分には到達しない */
}
