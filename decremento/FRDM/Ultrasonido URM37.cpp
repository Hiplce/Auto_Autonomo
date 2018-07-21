#include "mbed.h"
//#include "PwmIn.h"
#include "SoftwarePWM.h"
#include "Servo.h"
// main de los main
Serial pc(USBTX,USBRX);
const float e = 2.71828182845904;
//DigitalOut led(LED1);
DigitalOut led1(LED2);

//Motor
PwmOut pwm(PTC3);        //pwm motor
DigitalOut pina(D0);     //pin direccion
DigitalOut pinb(D1);     //pin direccion

//Ultrasonido
DigitalOut URTRIG(PTD1);          // A low pull on pin COMP/TRIG
InterruptIn event(PTD3);
Timer timer;
int begin, end;
int dist = 0;
//const float razon = 0.3f;

void PWM_rise()                  //invocado por PWM_Mode para medicion de ultrasonido
{
    end = timer.read_us();
    timer.stop();
    int DistanceMeasured = end - begin;

    if(DistanceMeasured>=10200) {
        // the reading is invalid.
        dist = 0;
        //printf("Invalid \n");
    } else {
        dist=abs(DistanceMeasured/50);           // every 50us low level stands for 1cm

    }
}
void PWM_Mode()                //invocado por event.fall() para lectura de ultrasonido
{

    URTRIG = 1;
    URTRIG = 0;         // reading Pin PWM will output pulses
    timer.start();
    begin = timer.read_us();
    event.rise(&PWM_rise);
    //event.fall(&PWM_rise);
}
int main()
{
  printf("holaaaaa\n");
  //  pwm.period_ms(5);       //periodo del pwm del motor

    //curva(5,100,40);
    //wait_ms(300);
    //vel(0);
    //while(1){}
    while(1) {
        event.fall(&PWM_Mode);    //linea 47
        PWM_Mode();       //no borrar por ningun motivo, aunque este bien fundamentado
        printf("distancia:  %d\n",dist);
        //event.rise(&PWM_Mode);    //linea 47
////////////////////////////////////////////////   DECREMENTO
if(dist >= 100 || dist == 0) {
    //vel(1);
    printf("adelante    %d\n", dist);
}
 if(dist < 92 && dist > 20)
{
  float algo = (10+0.7*pow(e,float((dist-45)/10)));
      printf("reg:    %d    vel:  %.2f\n\r",dist, algo);

    //vel(dist*razon/100);
    //  printf("%.2f cm \n", dist);
}

if(dist < 20)
{
    printf("atras    %d\n", dist);
    //vel(-0.2);
    //wait(0.1);
    //vel(0);
    //wait(1);
    /*while(dist < 20 && dist != 0)
    {
        event.fall(&PWM_Mode);    //linea 47
        PWM_Mode();       //no borrar por ningun motivo, aunque est� bien fundamentado
    }*/
}
//////////////////////////////////////////////// FIN DECREMENTO


        wait_ms(90);
    }
}
