#include "mbed.h"
#include "hcsr04.h"

PwmOut pwm1(PTC4);
PwmOut pwm2(PTD3);
//DigitalOut led(LED1);
//DigitalOut led1(LED2);
long dist_fder;
long dist_fizq;
float velocidad;
const float razon = 1.25f;
Serial pc(USBTX,USBRX);

HCSR04 sonar_fizq(D6,D7);
HCSR04 sonar_fder(D10,D11);


float d_prom()
{
    int dist_t = 0;
    int cont = 0;
    for(int i = 0; i <= 9; i++) {
        dist_fizq = sonar_fizq.distance();
        dist_fder = sonar_fder.distance();
        wait(0.001f);

        if(abs(dist_fder - dist_fizq) < 15) {
            dist_t += dist_fizq + dist_fder;
            cont += 2;
        } else {
            i--;
        }
    }
    return(dist_t/cont);
}
void vel(int pot)
{
    if (pot >= 0) {
    pwm1 = pot;
    pwm2 = 0.0f;
    }
    else {
        pwm2 = abs(pot)/100;
        pwm1 = 0.0f;
    }

}

int main()
{
    pwm1.period_ms(5);
    pwm2.period_ms(5);
    
    long dist;
    while(1) {
        dist = d_prom();
        //printf("%l", dist);
        if(dist >= 100.0f || dist == 0) {
            vel(1.0f);
        } else if(dist < 19.0f) {
            vel(-0.9f);
            wait(0.3);
            vel(0.0f);
        } else {
            velocidad = (dist - 20.0f)*razon;
            vel(velocidad);
            printf("%.2f cm \n", dist);
        }
        /*
                dist_fizq = sonar_fizq.getCm();
                dist_fder = sonar_fder.getCm();
                printf("%.2f cm   ", dist_fizq);
                printf("%.2f cm   ", dist_fder);
                printf("%.2f cm \n", (dist_fder+dist_fizq)/2);
                wait(0.1f);
        */

    }
}
