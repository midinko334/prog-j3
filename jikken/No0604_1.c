#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pigpiod_if2.h>
#include <pthread.h>
 
#define HIGH 1
#define LOW  0
#define LEDPIN 17
#define LOOPCOUNT 100
#define THREAD 2

void *thread(void *k){

	int i=*(int*)k,l=*(((int*)k)+1),pd,t;

	pd = pigpio_start(NULL,NULL);
	if (pd < 0){
		printf("pigpiod の接続に失敗しました。\n");
		printf("pigpiod が起動しているか確認してください。\n");
		exit(EXIT_FAILURE);
	}

	set_mode(pd,LEDPIN-l,PI_OUTPUT);

	t = 0;
	while(t < LOOPCOUNT){
	    for(int j=0;j<i;j++){
		gpio_write(pd,LEDPIN-l,HIGH);
		usleep(1000);
		}
	    for(int j=0;j<9-i;j++){
		gpio_write(pd,LEDPIN-l,LOW);
		usleep(1000);
		}
		t++;
	}
 
	gpio_write(pd,LEDPIN-l,LOW);
	usleep(2000);
	pigpio_stop(pd);
	usleep(2000);
	exit(1);

}

int main()
{

	int i[THREAD*2];
	for(int j=0;j<THREAD;j++) i[j]=-1;
	pthread_t th[THREAD];

	for(int j=0;j<THREAD;j++){
		while(i[j*2]<0||i[j*2]>=10){
			printf("明るさ%d:",j);
			scanf("%d",&i[j*2]);
		}
		i[j*2+1]=j;
	}

	for (int j=0;j<THREAD;j++) {
		pthread_create(&th[j], NULL, thread, (void*)&i[j*2]);
	}

	for (int j=0;j<THREAD;j++) {
		pthread_join(th[j], NULL);
	}

	return 0;
}
