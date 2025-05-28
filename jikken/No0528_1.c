#include <wiringPi.h>
#include <stdio.h>

#define GPIO 17

int main(void){

    int i;

    if(wiringPiSetupGpio()==-1) return 1;

    pinMode(GPIO, PWM_OUTPUT);//GPIOをPWM出力に設定
    pwmSetMode(PWM_MODE_MS);//markspaceモードに設定
    pwmSetClock(400);//クロック数を設定
    pwmSetRange(10);//レンジを設定

    scanf("%d",&i);

    pwmWrite(GPIO,i);
    delay(5000);
    pwmWrite(GPIO,0);

    return 0;
}
