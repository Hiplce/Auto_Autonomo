#include "mbed.h"
#include "SoftwarePWM.h"
#include "Servo.h"
#include "hcsr04.h"
// main de los main
Serial pc(USBTX,USBRX);

//ultrasonido
HCSR04 ultra(PTD3,PTD1);
const float e = 2.71828182845904;//valor de exponencial
bool menor20 = true;
//DigitalOut led(LED1);
DigitalOut led1(LED2);

//Motor
PwmOut pwm(PTC3);        //pwm motor
DigitalOut pina(D0);     //pin direccion
DigitalOut pinb(D1);     //pin direccion

//Ultrasonido
//DigitalOut URTRIG(PTD1);          // A low pull on pin COMP/TRIG
//InterruptIn event(PTD3);

Timer timer;
int begin, end;
long dist = 0;

int est = 1;
int estant = 1;
/*
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
}*/
void vel(float pot)                    //controlar motor mediante pin (pwm, pina, pinb)
{
    if(pot >= 0 ) {
        pina = 1;
        pinb = 0;
        pwm = pot*0.01;
    } else {
        pina = 0;
        pinb = 1;
        pwm = abs(pot)*0.01;
    }
}

void curva(float partes, int tiempo, float vel_max)
{
  int velocidad;
    for(int i=1; i <= partes; i++)
    {
      velocidad = (vel_max/partes)*i;
      ultra.distance();
       //algo = (10+0.7*pow(e,float((dist-45)/10))
      if(velocidad > ((log10(-10/0.7)/log10(e))*10+45))
      {
        break;
      }
      vel(velocidad);
      wait_ms(tiempo);
    }
}

int main()
{
  led1 = 1;
    pwm.period_ms(5);       //periodo del pwm del motor

    curva(5,100,40);
    //while(1){}
    while(1) {
      dist = ultra.distance();
        //event.fall(&PWM_Mode);    //linea 47
        //PWM_Mode();       //no borrar por ningun motivo, aunque este bien fundamentado

        printf("distancia:  %l\n",dist);

////////////////////////////////////////////////   DECREMENTO
        if(dist < 92 && dist > 25)//1
        {
          estant = 1;
            float algo = (10+0.7*pow(e,float((dist-45)/10)));
            printf("reg:    %d    vel:  %.2f\n\r",int(dist), algo);
            vel(algo);
            led1 = 0;
            wait_ms(((95-dist)*dist)/35);
            led1 = 1;
            wait_ms(((95-dist)*dist)/35);
        }
        if(dist < 25 && dist != 0)//2
        {
          estant = 2;
          /*  while(menor20 == true)
            {
            dist = ultra.distance();
            vel(-15);
            if(dist > 18)
            {*/
              vel(0);
            /*  menor20 = false;
            }
                //event.fall(&PWM_Mode);    //linea 47
                //PWM_Mode();       //no borrar por ningun motivo, aunque est� bien fundamentado
            }
            printf("atras    %d\n", int(dist));
            menor20 = true;*/
        }
        if(dist >= 92 || dist == 0)//3
        {
          if(estant == 2)
          {
            curva(5,100,40);
          }
          estant = 3;
            vel(40);
            printf("adelante    %d\n", int(dist));
        }
//////////////////////////////////////////////// FIN DECREMENTO
        wait_ms(20);
    }
}
