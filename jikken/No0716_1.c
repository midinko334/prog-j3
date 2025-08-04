#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
#include <pigpiod_if2.h>

#define DEFPIN 17
#define DETECTER 16
#define PATTERN 6
int saikoro(void);

// 0〜9 のセグメントパターン（0 = OFF, 1 = ON）
const int digits[PATTERN+1][8] = {
//  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
/*  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}, // 9
  {1,1,1,0,1,1,1,1}, // A
  {1,1,1,1,1,1,1,1}, // B
  {1,0,0,1,1,1,0,1}, // C
  {1,1,1,1,1,1,0,1}, // D
  {1,0,0,1,1,1,1,1}, // E
  {1,0,0,0,1,1,1,1}, // F*/
  {0,0,0,0,0,0,0,0}  // reset
};

void *thread(void *k){

	int pd[8];
	int id,state,count,quit;

	id=pigpio_start(NULL,NULL);
        if (id < 0){
            printf("pigpiod の接続に失敗しました。\n");
            printf("pigpiod が起動しているか確認してください。\n");
            exit(EXIT_FAILURE);
        }
        for(int t=0;t<8;t++){
            pd[t]=pigpio_start(NULL,NULL);
            if (pd[t] < 0){
                printf("pigpiod の接続に失敗しました。\n");
                printf("pigpiod が起動しているか確認してください。\n");
                exit(EXIT_FAILURE);
            }
	}
	set_mode(id,DETECTER,PI_INPUT);
	set_pull_up_down(id,DETECTER,PI_PUD_UP);
	for(int t=0;t<8;t++) set_mode(pd[t],t+DEFPIN,PI_OUTPUT);

  int flag=0,num=0;
  while(1){
    while(1){
      state = gpio_read(id,DETECTER);
      if(state==flag%2) count++;
      else count=0;
      if(count>20){
	count=0;
	break;
      }
      if(state==0) quit++;
      else quit=0;
      if(quit>2000){
	for(int t=0;t<8;t++) gpio_write(pd[t],t+DEFPIN,digits[PATTERN][t]);
        for(int i=0;i<8;i++) pigpio_stop(pd[i]);
	usleep(2000);
	pthread_exit((void *)0);
      }
      if(flag%2==0) num++;
      if(flag%2) for(int t=0;t<8;t++) gpio_write(pd[t],t+DEFPIN,digits[num%6][t]);
      usleep(1000);
    }
    flag++;
  }

  //この部分には到達しない
}

int main(void){
  pthread_t th[THREAD];
  pthread_create(&th[j], NULL, thread, (void*)&i[j*2]);
  pthread_join(th[j], NULL);
}
