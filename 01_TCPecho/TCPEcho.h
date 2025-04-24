#define MAXPENDING 5   /* 同時にキュー可能な接続要求の最大数 */
#define RCVBUFSIZE 4096  /* 受信バッファのサイズ */

void DieWithError(char *errorMessage);  /* エラー処理関数 */
void HandleTCPClient(int clntSocket);   /* TCPクライアント処理関数 */
