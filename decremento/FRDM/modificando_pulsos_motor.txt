#include "mbed.h"
#include "PwmOut.h"
#include "Serial.h"

PwmOut pwmsal(PTC3);
//PwmOut pwmled(LED1);
Serial pc(USBTX,USBRX);
uint16_t periodpwmsal=1;
//uint16_t periodpwmled=1;
float dutypwmsal=0;
//float dutypwmled=0;

void rxinterrupt()
{
    switch (pc.getc()){

        case 'q':

            periodpwmsal++;
            //periodpwmled++;
            pwmsal.period_ms(periodpwmsal);
            //pwmled.period_ms(periodpwmsal);
            break;


        case 'a' :
            if (periodpwmsal>1){
                periodpwmsal=periodpwmsal-1;
                //periodpwmled=periodpwmled-1;
            }
            pwmsal.period_ms(periodpwmsal);
            //pwmled.period_ms(periodpwmled);
            break;

        case 'w':
            if(dutypwmsal<1) {
                dutypwmsal=dutypwmsal+0.05;   // aumentamos el %5 del dutty cycle
                //dutypwmled=dutypwmled+0.05;
            }
            pwmsal.write(dutypwmsal);
            //pwmled.write(dutypwmled);
            break;
        case 's':
            if(dutypwmsal>0) {
            dutypwmsal=dutypwmsal-0.05;   // disminuimos el %5 del dutty cycle
            //dutypwmled=dutypwmled-0.05;
        }
        pwmsal.write(dutypwmsal);
        //pwmled.write(dutypwmled);
        break;
    default : break;
    }
    pc.printf("PeriodoPWM:%d DutyCicle %.2f porciento\r\n",periodpwmsal,dutypwmsal*100);
 }


            int main() {
            pc.baud(9600);
            pc.attach(&rxinterrupt);



                while(1);

            }