#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
#include <pigpiod_if2.h>

#define DEFPIN 17

// 0〜9 のセグメントパターン（0 = OFF, 1 = ON）
const int digits[10][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,1}  // 9
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
    for (int num = 0; num <= 9; num++) {
      for(int t=0;t<8;t++) gpio_write(pd[t],t+DEFPIN,digits[num][t]);
      sleep(1);
    }
  }

  pigpio_stop(pd);
  return 0;
}
