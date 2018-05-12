#include <Servo.h>
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
// Direccion

Servo serd;
Servo sl1;


void setup() {
  // put your setup code here, to run once:
  /*
  definir rangos que no me acuerdo como hacerlo en arduino
  */
  Serial.begin(115200);
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  serd.write(0);
  sl1.write(0);
  lox.rangingTest(&measure, false);
  int distl1; // 
  int posIni = 0; // esta posicion va a estar definida para el bno despues
  int pos[12] = {-90,-60,-30,30,60,90,60,30,-30,-60,-90}; // lo pongo asi para hacer un solo for
  int distl[12];
  int pa;
  for(int i = 0; i<11; i++) {
            sl1.write(pos[i]);
            delay(150);
            //distl[i] = l1.pulsewidth()*10000;        //guardado de las 6 lecturas de izq. a der.
            distl[i] = distl1; // no encontre la libreria del laser que tenia mariano habria que agregarla para tomar el valor
            //printf("posicion %d : %.2f\n",i,distl[i]);
            if (distl[i] < 45) {
                if(i<2) {
                    pa = posIni;
                    while((l1.pulsewidth()*10000)<42 && pa>-90) {   //cambiar la condicion por la lectura del sensor
                        //printf("se rompio aca1\n");
                        //printf("posicion actual: %d\n",pa);
                        pa--;
                        serd.write(pa);


                    }
                    serd.write(posIni);
                } else {
                    pa = posIni;
                    while((l1.pulsewidth()*10000)<42 && pa<90) {//lo mismo aca
                        // printf("se rompio aca2\n");    //la direccion se mueve a la izquierda
                       // printf("posicion actual: %d\n",pa);
                        pa++;
                        serd.write(pa);

                    }
                    serd.write(posIni);
                }
            }
        }

}
