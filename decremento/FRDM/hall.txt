#include "mbed.h"

PwmOut pwm1(PTD3);
PwmOut pwm2(PTA2);

DigitalIn hall(PTB9);
DigitalOut led(LED1);
Serial pc(USBTX,USBRX);
int main()
{
    pwm1.period_ms(5);
    pwm2.period_ms(5);
    while(true)
    {
    pwm2 = 0.0f;
    pwm1 = 1.0f;
    wait(7);
    pwm1 = 0.0f;
    pwm2 = 1.0f;
    wait(7);
    }
    /*
    led = 1;
    int cont=0;
    int algo;
    while (true) {
       algo = hall;
       pc.printf("%d     %d \n", algo, cont);
       if(algo == 1)
       {
           while(algo == 1)
           {
                algo = hall;
           }
           cont++;
       }
    }
    led=0;
    return(0);
    */


}