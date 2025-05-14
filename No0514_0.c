#include <stdio.h>
#include <stdlib.h>
 
#include <pigpiod_if2.h>
 
#define HIGH 1
#define LOW  0
#define LEDPIN 17
#define LOOPCOUNT 10
 
int main()
{
	int pd, t;
 
	pd = pigpio_start(NULL,NULL);
	if (pd < 0){
		printf("pigpiod の接続に失敗しました。\n");
		printf("pigpiod が起動しているか確認してください。\n");
		exit(EXIT_FAILURE);
	}
 
	printf("\nLEDが0.5秒ごとに点灯と消灯を繰り返すプログラム\n");
	printf("LED点灯回路は GPIO17 に接続されていること！\n");
 
	set_mode(pd,LEDPIN,PI_OUTPUT);
 
	t = 0;
	while(t < LOOPCOUNT){
		gpio_write(pd,LEDPIN,HIGH);
		time_sleep(0.5);
		gpio_write(pd,LEDPIN,LOW);
		time_sleep(0.5);
		t++;
	}
 
	pigpio_stop(pd);
 
	return 0;
}
