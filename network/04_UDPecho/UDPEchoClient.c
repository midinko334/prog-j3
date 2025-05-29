/*●●● この行の下に必要なヘッダファイルを列挙する． ●●●*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define ECHOMAX  255  /* エコー文字列の最大長 */

void DieWithError(char  *errorMessage);  /* 外部エラー処理関数 */

int main(int  argc, char  *argv[])
{
  int  sock;  /* ソケットディスクリプタ */
  struct sockaddr_in  echoServAddr;  /* エコーサーバのアドレス */
  struct sockaddr_in  fromAddr;  /* エコー送信元のアドレス */
  unsigned short  echoServPort;  /* エコーサーバのポート番号 */
  unsigned int  fromSize;  /* recvfrom()のアドレスの入出力サイズ */
  char  *servIP;  /* サーバのIPアドレス */
  char  *echoString;  /* エコーサーバへ送信する文字列 */
  char  echoBuffer[ECHOMAX+1];  /* エコー文字列の受信用バッファ */
  int  echoStringLen;  /* エコー文字列の長さ */
  int  respStringLen;  /* 受信した応答の長さ */
  int  sendStringLen;  /* 送信した応答の長さ */

  if ((argc -1 < 2) || (argc -1 > 3)) { /* 引数の数が正しいか確認 */
    fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n", 
	    argv[0]);
    exit(1);
  }

  /*●●● 右辺 ●●●*/
  servIP = argv[1];  /* 1つ目の引数：サーバのIPアドレス（dotted quad）*/

  /*●●● 右辺 ●●●*/
  echoString = argv[2];  /* 2つ目の引数：エコー文字列 */

  /* 入力した文字列の長さをチェック */
  /*●●● 右辺 ●●●*/
  echoStringLen = strlen(echoString);
  if (echoStringLen > ECHOMAX) {
    DieWithError("Echo word too long");
  }

  if (argc -1 == 3) {
    /*●●● 右辺 ●●●*/
    echoServPort = atoi(argv[3]);  /* 指定のポート番号があれば使用 */
  } else {
    echoServPort = 7;  /* 7はエコーサービスのwell-knownポート番号 */
  }

  /* UDPデータグラムソケットの作成 */
  /*●●● socket() の引数 ●●●*/
  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock < 0) {
    DieWithError("socket() failed");
  }


  /* サーバのアドレス構造体の作成 */
  /*●●● memset() の引数 ●●●*/
  memset(&echoServAddr, 0, sizeof(echoServAddr));  /* 構造体にゼロを埋める */

  /*●●● 右辺 ●●●*/
  echoServAddr.sin_family = AF_INET;  /* インターネットアドレスファミリ */

  /*●●● 右辺 ●●●*/
  echoServAddr.sin_addr.s_addr = inet_addr(servIP);  /* サーバのIPアドレス */

  /*●●● 右辺 ●●●*/
  echoServAddr.sin_port = htons(echoServPort);  /* サーバのポート番号 */

  /* 文字列をサーバに送信 */
  /*●●● sendto() の引数 ●●●*/
  sendStringLen = sendto(sock, echoString, echoStringLen, 0, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr));
  if (sendStringLen != echoStringLen) {
    DieWithError("sendto() sent a different number of bytes than expected");
  }

  /* 応答を受信 */
  fromSize = sizeof(fromAddr);

  /*●●● recvfrom() の引数 ●●●*/
  respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr *) &fromAddr, &fromSize);
  if (respStringLen != echoStringLen) {
    DieWithError("recvfrom() failed");
  }

  /*●●● if 文の条件 ●●●*/
  if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr) {
    fprintf(stderr, "Error: received a packet from unknown source.\n");
    exit(1);
  }

  /* 受信データをNULL文字で終端させる */
  /*●●● 右辺 ●●●*/
  echoBuffer[respStringLen] = '\0';
  printf("Received: %s\n", echoBuffer); /* 引数のエコー文字列を表示 */

  close(sock);
  return 0;
}
