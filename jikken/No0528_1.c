#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pigpiod_if2.h>
 
#define HIGH 1
#define LOW  0
#define LEDPIN 17
#define LOOPCOUNT 10000
 
int main()
{
	int pd, t,i;
 
	pd = pigpio_start(NULL,NULL);
	if (pd < 0){
		printf("pigpiod の接続に失敗しました。\n");
		printf("pigpiod が起動しているか確認してください。\n");
		exit(EXIT_FAILURE);
	}
 
	printf("明るさ:");
	scanf("%d",&i);

	set_mode(pd,LEDPIN,PI_OUTPUT);
 
	t = 0;
	while(t < LOOPCOUNT){
		gpio_write(pd,LEDPIN,HIGH);
		usleep(i*1000);
		gpio_write(pd,LEDPIN,LOW);
		usleep((9-i)*1000);
		t++;
	}
 
	pigpio_stop(pd);
 
	return 0;
}
