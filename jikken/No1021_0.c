#include <stdio.h>
#include <stdlib.h>
#include <pigpiod_if2.h>

#define PWMPIN 18

#define SERVOCENTER 1450    // 中央(0°)
#define SERVOMAX   2200     // +90°
#define SERVOMIN    500     // -90°
#define PWMFREQ      50     // 50Hz(周期20ms)

void software_pwm_servo(int pd, int pin, int pulse_width_us)
{
    // 1周期
    int period_us = 1000000 / PWMFREQ;
    int off_time = period_us - pulse_width_us;

    // HIGH時間
    gpio_write(pd, pin, 1);
    time_sleep(pulse_width_us / 1000000.0);

    // LOW時間
    gpio_write(pd, pin, 0);
    time_sleep(off_time / 1000000.0);
}

int main()
{
    int pd, angle, qflag;
    int pulse_width;

    pd = pigpio_start(NULL, NULL);
    if (pd < 0) {
        printf("pigpiod の接続に失敗しました。\n");
        exit(EXIT_FAILURE);
    }

    set_mode(pd, PWMPIN, PI_OUTPUT);

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
        scanf("%d", &angle);

        if ((angle >= -90) && (angle <= 90)) {
            pulse_width = SERVOCENTER + (angle / 90.0) * (SERVOMAX - SERVOCENTER);

            // 安定するまで何回か送る（例:40ms程度）
            for(int i=0;i<4;i++){
                software_pwm_servo(pd, PWMPIN, pulse_width);
            }
        } else {
            qflag = 1;
        }
    }

    // 中央に戻す
    pulse_width = SERVOCENTER;
    for(int i=0;i<10;i++){
        software_pwm_servo(pd, PWMPIN, pulse_width);
    }

    gpio_write(pd, PWMPIN, 0);
    pigpio_stop(pd);
    return 0;
}
