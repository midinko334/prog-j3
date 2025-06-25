#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
#include <pigpiod_if2.h>

#define DEFPIN 17

// 0〜9 のセグメントパターン（0 = OFF, 1 = ON）
const int digits[17][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}, // 9
  {1,1,1,0,1,1,1,1}, // A
  {1,1,1,1,1,1,1,1}, // B
  {1,0,0,1,1,1,0,1}, // C
  {1,1,1,1,1,1,0,1}, // D
  {1,0,0,1,1,1,1,1}, // E
  {1,0,0,0,1,1,1,1}, // F
  {0,0,0,0,0,0,0,0}  // reset
};

int main(void) {

	int pd[8];
 
        for(int t=0;t<8;t++){
            pd[t]=pigpio_start(NULL,NULL);
            if (pd[t] < 0){
                printf("pigpiod の接続に失敗しました。\n");
                printf("pigpiod が起動しているか確認してください。\n");
                exit(EXIT_FAILURE);
            }
	}
	for(int t=0;t<8;t++) set_mode(pd[t],t+DEFPIN,PI_OUTPUT);

  for(int i=0;i<1;i++){
    for (int num = 0; num < 17; num++) {
      for(int t=0;t<8;t++) gpio_write(pd[t],t+DEFPIN,digits[num][t]);
      sleep(1);
    }
  }

  for(int i=0;i<8;i++) pigpio_stop(pd[i]);
  return 0;
}
