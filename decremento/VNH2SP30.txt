#include "mbed.h"

#define BRAKEVCC 0
#define CW 1
#define CCW 2
#define BRAKEGND 3
#define CS_THRESHOLD 15   // Definición de la cadena de segurodad (ver: " 1.3) Ejemplo Monster Shield" ).

int i=0;

PwmOut pwm(PTC2); //pwm motor
DigitalOut pina(D6); //pin direccion
DigitalOut pinb(D5); //pin direccion
AnalogIn cspin(A0); //nos dice si el motr esta trabado

DigitalOut statpin(LED1);

int main()
{
    while(true) 
    {
            int med = cspin;
            if (med > CS_THRESHOLD)
            {
                vel(0.0f);
            }
            
            statpin = 1;
    }
}
    
    void vel(float pot) 
    {       
        if(pot >= 0)
        {
            pina = 1;
            pinb = 0;
            pwm = pot*0.01;
        }
        else
        {  
            pina = 0;
            pinb = 1;
            pwm = abs(pot)*0.01;
        }
    }