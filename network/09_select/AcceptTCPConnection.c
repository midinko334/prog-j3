/*●●● 必要なヘッダファイルを列挙する ●●●*/
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void  DieWithError(char  *errorMessage);  /* エラー処理関数 */

int  AcceptTCPConnection(int  servSock)
{
  int  clntSock;                     /* クライアントのソケットディスクリプタ */
  struct sockaddr_in  echoClntAddr;  /* クライアントのアドレス */
  unsigned int  clntLen;             /* クライアントのアドレス構造体の長さ */

  /* 入出力パラメータのサイズをセット */
  /*●●● 右辺 ●●●*/
  clntLen = sizeof(echoClntAddr);

  /* クライアントからの接続要求を待つ */
  /*●●● accept() の引数 ●●●*/
  clntSock = accept(servSock, (struct sockaddr*)&echoClntAddr, &clntLen);
  if (clntSock < 0) {
    DieWithError("accept() failed");
  }

  /* clntSockはクライアントに接続済み */
  printf ("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

  return clntSock;
}
