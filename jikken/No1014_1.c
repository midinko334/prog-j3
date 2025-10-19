#include <stdio.h>
#include <stdlib.h>
#include <pigpiod_if2.h>

// コンパイルと実行方法
//  gcc -Wall -pthread -o 出力ファイル名 ソースファイル名 -lpigpiod_if2 -lrt

// PWM に使用する GPIO のピン番号
#define PWMPIN 18

// サーボモータの中央位置（0度）のパルス幅(us)を定義する
#define SERVOCENTER 1450

// サーボモータの右位置（+90 度）のパルス幅(us)を定義する
#define SERVOMAX 2400

// サーボモータの左位置（‐90 度）のパルス幅(us)を定義する
#define SERVOMIN 500

// 発生させる PWM周期[Hz]を定義する
#define PWMFREQ 50

int main()
{
    int pd, angle, qflag, duty;

    // 最初にデーモンに接続する（NULL:localhost, NULL:default port）
    pd = pigpio_start(NULL, NULL);
    if (pd < 0) {
        printf("pigpiod の接続に失敗しました。\n");
        printf("pigpiod が起動しているか確認してください。\n");
        printf(" 毎回手動で起動する方法：sudo pigpiod\n");
        printf(" 自動的に起動させる方法：sudo systemctl enable pigpiod.service; reboot\n");
        exit(EXIT_FAILURE);
    }

    printf("\n");
    printf("************************************\n");
    printf("|    servo control                 |\n");
    printf("|  ------------------------------  |\n");
    printf("|   PWM(Orange) connect to GPIO18  |\n");
    printf("|   Vcc(Red) connect to +5V        |\n");
    printf("|   GND(Brown) connect to GND      |\n");
    printf("|                                  |\n");
    printf("************************************\n");

    qflag = 0;
    while (qflag == 0) {
        printf("\nInput angle (left side:-90 ~ 0 ~ +90:right side) : ");
        scanf("\n%d", &angle);
        if ((angle >= -90) && (angle <= 90)) {
            // ここで与えられた角度からデューティ比を計算する
            duty=(SERVOCENTER+(angle/90.0)*(SERVOMAX-SERVOCENTER))*PWMFREQ;
            hardware_PWM(pd, PWMPIN, PWMFREQ, duty);
        } else {
            qflag = 1;
        }
    }

    // 終了時の処理として中央位置（0度）にする
    // 中央位置に戻すためのデューティ比を計算する
    duty = SERVOCENTER*PWMFREQ;
    hardware_PWM(pd,PWMPIN,PWMFREQ,duty);
    time_sleep(0.5); // 中央に戻る時間を保証するための待ち時間

    // PWM 出力の停止（デューティ比を 0として指定する）
    hardware_PWM(pd,PWMPIN,PWMFREQ,0);

    // 最後にデーモンと切断する
    pigpio_stop(pd);
    return 0;
}
