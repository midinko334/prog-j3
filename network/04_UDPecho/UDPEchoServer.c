/*●●● この行の下に必要なヘッダファイルを列挙する． ●●●*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define ECHOMAX  255  /* エコー文字列の最大長 */

void DieWithError(char *errorMessage);  /* 外部エラー処理関数 */

int main(int argc, char *argv[])
{
  int  sock;  /* ソケット */
  struct sockaddr_in  echoServAddr;  /* ローカルアドレス */
  struct sockaddr_in  echoClntAddr;  /* クライアントアドレス */
  unsigned int  cliAddrLen;  /* 着信メッセージの長さ */
  char  echoBuffer[ECHOMAX];  /* エコー文字列用バッファ */
  unsigned short  echoServPort;  /* サーバのポート番号 */
  int  recvMsgSize;  /* 受信メッセージのサイズ */
  int  res_bind;  /* bind() の戻り値を入れる． */
  int  res_sendto;  /* sendto() の戻り値を入れる． */

  /*●●● if 文の条件 ●●●*/
  if (argc != 2) {  /* 引数の個数が正しいか確認 */
    fprintf(stderr, "Usage: %s <UDP SERVER PORT>\n", argv[0]);
    exit(1);
  }

  echoServPort = atoi(argv[1]);  /* 1つ目の引数：ローカルポート番号 */

  /* データグラムの送受信に使うソケットを作成 */
  /*●●● socket() の引数 ●●●*/
  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock < 0) {
    DieWithError("socket() failed");
  }

  /* ローカルのアドレス構造体を作成 */
  /*●●● memset() の引数 ●●●*/
  memset(&echoServAddr, 0, sizeof(echoServAddr));  /* 構造体にゼロを埋める */

  /*●●● 右辺 ●●●*/
  echoServAddr.sin_family = AF_INET;  /* インターネットアドレスファミリ */

  /*●●● 右辺 ●●●*/
  echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* ワイルドカードを使用 */

  /*●●● 右辺 ●●●*/
  echoServAddr.sin_port = htons(echoServPort);  /* ローカルポート */

  /* ローカルアドレスへバインド */
  /*●●● bind() の引数 ●●●*/
  res_bind = bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr));
  if (res_bind < 0) {
    DieWithError("bind() failed");
  }

  for (;;) /* プログラムが終了するまで繰り返し実行 */
  {
    /* 入出力パラメータのサイズをセット */
    cliAddrLen = sizeof(echoClntAddr);

    /* クライアントからメッセージを受信するまでブロックする  */
    /*●●● recvfrom() の引数 ●●●*/
    recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr *) &echoClntAddr, &cliAddrLen);
    if (recvMsgSize < 0) {
      DieWithError("recvfrom() failed");
    }

    printf("Handling client %s\n", inet_ntoa(echoClntAddr. sin_addr));

    /* 受信したデータグラムをクライアントに返信する */
    /*●●● sendto() の引数 ●●●*/
    res_sendto = sendto(sock, echoBuffer, recvMsgSize, 0, (struct sockaddr *) &echoClntAddr, sizeof(echoClntAddr));
    if (res_sendto != recvMsgSize) {
      DieWithError("sendto() sent a different number of bytes than expected");
    }
  }
  /* この部分には到達しない*/
}
