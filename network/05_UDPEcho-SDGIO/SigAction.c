/*●●● 必要なヘッダファイルを列挙する ●●●*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void  DieWithError(char  *errorMessage);        /* エラー処理関数 */
void  InterruptSignalHandler(int  signalType);  /* 割り込みシグナル処理関数 */


int main(int argc, char *argv[])
{
  struct sigaction  handler;  /* シグナルハンドラを指定する構造体 */
  int ret_sigfillset;  /*●●● 型を記述する ●●●*/
  int ret_sigaction;   /*●●●  型を記述する ●●●*/

  /* InterruptSignalHandler()をハンドラ関数として設定 */
  /*●●● 右辺 ●●●*/
  handler.sa_handler = InterruptSignalHandler;

  /* 全シグナルをマスクするマスクを作成 */
  /*●●●  sigfillset() の引数 ●●●*/
  ret_sigfillset = sigfillset(&handler.sa_mask);
  if (ret_sigfillset < 0) {
    DieWithError("sigfillset() failed");
  }

  /* フラグなし */
  handler.sa_flags = 0;

  /* 割り込みシグナルに対する処理を設定 */
  /*●●●  sigaction() の引数 ●●●*/
  ret_sigaction = sigaction(SIGINT, &handler, NULL);
  if (ret_sigaction < 0) {
    DieWithError("sigaction() failed");
  }

  for ( ; ; ) {
    pause();  /* シグナルを受け取るまでプログラムを一時停止 */
  }

  return 0;
}


void InterruptSignalHandler(int  signalType)
{/* sigfillset()の戻り値 */
    int ret_sigaction;         /* sigaction()の戻り値 */

  /*●●● 作業内容を記述する ●●●*/
    printf("\n");
    sleep(1);
    printf("Interrupt Received.  Exiting program.\n");
    exit(0);

}
