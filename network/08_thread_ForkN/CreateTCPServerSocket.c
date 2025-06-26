/*●●● 必要なヘッダファイルを列挙する ●●●*/
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5    /* 未処理の接続要求の最大値 */

void  DieWithError(char  *errorMessage); /* エラー処理関数 */


int  CreateTCPServerSocket(unsigned short  port)
{
  int  sock;                        /* 作成するソケット */
  struct sockaddr_in  echoServAddr; /* ローカルアドレス */
  int ret_bind;  /*●●● 型 ●●●*/
  int ret_listen;  /*●●● 型 ●●●*/

  /* 着信接続要求に対するソケットを作成 */
  sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock < 0) {
    DieWithError("socket() failed");
  }

  /* ローカルのアドレス構造体を作成 */
  memset(&echoServAddr, 0, sizeof(echoServAddr));  /* 構造体をゼロで埋める */
  echoServAddr.sin_family = AF_INET;  /* インターネットアドレスファミリ */
  echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* ワイルドカードを使用 */
  echoServAddr.sin_port = htons(port);  /* ローカルポート */

  /* ローカルアドレスへバインド */
  /*●●● bind() の引数 ●●●*/
  ret_bind = bind(sock, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr));
  if (ret_bind < 0) {
    DieWithError("bind() failed");
  }

  /* 着信接続要求のリスン中というマークをソケットに付ける */
  /*●●● listen() の引数 ●●●*/
  ret_listen =  listen(sock, MAXPENDING);
  if (ret_listen < 0) {
    DieWithError("listen() failed");
  }

  return sock;
}
