#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#include <pigpiod_if2.h>
 
#define HIGH 1
#define LOW  0
#define LEDPIN 17
#define LOOPCOUNT 30
 
int main()
{
	int pd, t;
	srand((unsigned)time(NULL));
 
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
        double o;
	while(t < LOOPCOUNT){
		gpio_write(pd,LEDPIN,HIGH);
		o=(double)rand()/2147483647;
		printf("%lf[s]\n",o);
		time_sleep(o);
		gpio_write(pd,LEDPIN,LOW);
		o=(double)rand()/2147483647;
		printf("%lf[s]\n",o);
		time_sleep(o);
		t++;
	}
 
	pigpio_stop(pd);
 
	return 0;
}
