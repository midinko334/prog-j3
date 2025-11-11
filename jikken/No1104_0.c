// 図 1 のデータ送信波形をよく理解してプログラムを作成すること！
// 特に立下りのタイミングや回数に注意すること！

#include <stdio.h>
#include <stdlib.h>
#include <pigpiod_if2.h>
#include <unistd.h>
#include <pthread.h>

int pd,qflag;
pthread_t p1;
char ans;
int SEG_PINS[8] = {5,6,13,19,12,16,20,21};
int DIGIT_PINS[4] = {4,17,27,22};
int DIGIT_CODE[10][8] = {
  {0,0,0,0,0,0,1,1},//0
  {1,0,0,1,1,1,1,1},//1
  {0,0,1,0,0,1,0,1},//2
  {0,0,0,0,1,1,0,1},//3
  {1,0,0,1,1,0,0,1},//4
  {0,1,0,0,1,0,0,1},//5
  {0,1,0,0,0,0,0,1},//6
  {0,0,0,1,1,1,1,1},//7
  {0,0,0,0,0,0,0,1},//8
  {0,0,0,0,1,0,0,1} //9
};

// コンパイルと実行方法
//  gcc -Wall -pthread -o dht11 dht11.c -lpigpiod_if2 -lrt
// 実行前に必ずデーモンをスタートさせること（起動時にスタートさせるのがよい）
//  sudo pigpiod
// 一旦、デーモンが起動すれば、プログラムを実行するだけ

// DHT11 が接続されているピン番号を定義すること
#define DHT11PIN 26

// バイトデータの並び順
#define HUMIUPPER 0
#define HUMILOWER 1
#define TEMPUPPER 2
#define TEMPLOWER 3
#define CHECKBYTE 4

// エッジ検出回数の最大数、ノイズ対応のためにかなり余裕をもたせている
#define MAXEDGECOUNT 100

// 正常なエッジ検出回数（全ての立下りの回数）
#define DETECTNUM 43

// ビット判定のパルス幅しきい値(us)
#define DETECTIONTH 100

// ロジックレベルの宣言
#define HIGH 1
#define LOW  0

// エッジ検出時に検出時間を格納する構造体の型宣言
typedef struct {
 unsigned int timedata[MAXEDGECOUNT]; //時間を記録するためのバッファ
 int p; // バッファポインタ
} tdata;

// プロトタイプ宣言
int bit_trans(tdata *td, int ofs);
void edge_detection(int pd, unsigned int gpio, unsigned int level, unsigned int tick, void* td);

void displayNumber(int pd, int num) {
    int digits[4];
    for (int i = 3; i >= 0; i--) {
        digits[i] = num % 10;
        num /= 10;
    }

    for (int i = 0; i < 4; i++) {
        for (int s = 0; s < 8; s++)
            gpio_write(pd, SEG_PINS[s], DIGIT_CODE[digits[i]][s]);

        for (int d = 0; d < 4; d++)
            gpio_write(pd, DIGIT_PINS[d], d == i ? 0 : 1);

        time_sleep(0.005);
    }
}

void *thread(void *p){
  int hu,hl,tu,tl,cb,cid;
  float temp,humi;
  tdata td;

  while(ans!='q'){
    // データ転送の準備（処理関数のセット）
    td.p = 0;
    // 指定されたピンの立下りで割り込み処理が生じるように設定する
    // edge_detection( )関数が割り込み時に呼び出される関数となる

    cid = callback_ex(pd, DHT11PIN, FALLING_EDGE, edge_detection, &td);
    if (cid < 0){
      printf("caillback_ex が失敗しました。\n");
      qflag = 1;
    } else {
      // スタート信号の作成（1回目の立下りになる）
      set_mode(pd, DHT11PIN, PI_OUTPUT); // スタート信号の開始（解放で 1→0）
      time_sleep(0.020);                 // 18ms 以上 30ms 以下の範囲で待つ
      set_mode(pd, DHT11PIN, PI_INPUT);  // スタート信号の終了（0→解放で 1）
      time_sleep(0.010); // データ転送を待つ（最大で 130us×40＝5.2ms 程度）

      // データ転送の終了（処理関数のキャンセル）とチェック
      if (callback_cancel(cid) != 0) printf("callback_cancel が失敗しました\n");

      printf("立ち下がり検出回数：%d\n",td.p);
      if (td.p != DETECTNUM){
        printf("データ読み出しに失敗しました！\n");
      }
      else {
        hu = bit_trans(&td, HUMIUPPER);
        hl = bit_trans(&td, HUMILOWER);
        tu = bit_trans(&td, TEMPUPPER);
        tl = bit_trans(&td, TEMPLOWER);
        cb = bit_trans(&td, CHECKBYTE);

        if ( ((hu + hl + tu + tl) & 0xFF) != cb ){
          printf("チェックバイトエラー！\n");
        }
        else {
            // 湿度の上位と下位を結合する（仕様上は下位は常に 0）
            humi = hu + (hl * 0.1f);
            // 温度の上位と下位を結合（下位の最上位ビットは除く）
            temp = tu + ((tl & 0x7F) * 0.1f);
            // 下位の最上位ビットが 1のときは温度が氷点下を示している
            if (tl & 0x80) temp = -temp;
            // 最後に、湿度と温度を表示する
            printf("湿度:%3.1f％, 温度:%2.1f℃\n",humi,temp);
	    displayNumber(pd, (int)temp);
            time_sleep(1.5);
	    displayNumber(pd, (int)humi);
	    time_sleep(1.5);
        }
      }
    }
  }

  return (NULL);

}

int main()
{
 for(int i = 0; i < 8; i++) set_mode(pd, SEG_PINS[i], PI_OUTPUT);
 for(int i = 0; i < 4; i++) set_mode(pd, DIGIT_PINS[i], PI_OUTPUT);

  // 最初にデーモンに接続する（NULL:localhost, NULL:default port）
  pd = pigpio_start(NULL,NULL);
  if (pd < 0){
    printf("pigpiod の接続に失敗しました。\n");
    printf("pigpiod が起動しているか確認してください。\n");
    printf(" 毎回手動で起動する方法：sudo pigpiod\n");
    printf(" 自動的に起動させる方法：sudo systemctl enable pigpiod.service; reboot");
    exit(EXIT_FAILURE);
  }

  // センサの仕様上、1回データを空読みしておく（データシート参照）
  set_pull_up_down(pd, DHT11PIN, PI_PUD_OFF); // GPIO ピンによってはプルダウン設定対策
  gpio_write(pd, DHT11PIN, LOW);    // スタート信号用に出力値を 0に設定しておく
  set_mode(pd, DHT11PIN, PI_OUTPUT); // スタート信号送信
  time_sleep(0.020);                // スタート信号生成用の時間待ち 20ms
  set_mode(pd, DHT11PIN, PI_INPUT); // スタート信号送信後は入力に、データ送信が開始
  printf("センサ初期化処理中につき、2秒お待ち下さい。\n"); // データは読む必要なし
  time_sleep(2.0); // 次の測定まで 2秒開ける必要がある

  printf("\n");
  printf("+-----------------------------+\n");
  printf("|    DHT11 connection         |\n");
  printf("|  -------------------------  |\n");
  printf("|   Data connected to GPIO    |\n");
  printf("|   Vcc  connected to +3.3V   |\n");
  printf("|   GND  connected to GND     |\n");
  printf("+-----------------------------+\n");
  printf("注意：センサの仕様上、データの再取得には 2秒以上の間隔を開けます。\n");

  pthread_create(&p1, NULL, &thread, NULL);

  qflag = 0;
  while(qflag == 0){
    printf("終了する[q]");
    scanf("%c",&ans);
    if (ans == 'q'){
      qflag = 1;
      pthread_join(p1, NULL);
    }
  }

  for (int i = 0; i < 8; i++) set_mode(pd, SEG_PINS[i], PI_OUTPUT);
  for (int i = 0; i < 4; i++) set_mode(pd, DIGIT_PINS[i], PI_OUTPUT);
  // 最後にデーモンと切断する
  pigpio_stop(pd);
  return 0;
}

// 記録された立下りの時間から 8ビット分を判定し、1バイトにして返す関数
// td：立下りの時間が記録されている構造体
// ofs：変換するデータの位置（バイト単位）が指定されている
int bit_trans(tdata *td, int ofs)
{
  int b,i,t,d,p;
  d = 0;
  for(i=0; i<8; i++){
    p = 3 + ofs*8 + i; // 先頭の3つの立下りの後に40ビット分の立下りが続く（3 + ofs*8 + i）
    t = (int)(td->timedata[p] - td->timedata[p-1]); // 前の立下りから今の立下りまでの差（us）
    if (t < DETECTIONTH) b = LOW;
    else b = HIGH;
    d = (d << 1) | (b & 0x1); // 上位ビットから詰める（MSBファースト）
  }
  return d;
}

// call back によって立下り時に呼び出される関数
// 呼び出されるたびに立下り時間 tick をバッファに記録していく
void edge_detection(int pd, unsigned int gpio, unsigned int level, unsigned int tick, void* td) // void* は型が未定義のポインタで任意の型のアドレスを格納できる 
{
  tdata *tdp;
  tdp = (tdata *)td;
  // ここにバッファへに記録するためのプログラムを書く
  if (tdp->p < MAXEDGECOUNT) {
    tdp->timedata[tdp->p] = tick;
    tdp->p++;
  }
}
