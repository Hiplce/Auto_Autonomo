#include <Wire.h> //bno
#include <Adafruit_Sensor.h> //bno
#include <Adafruit_BNO055.h> //bno
#include <utility/imumaths.h> //bno
#include <Servo.h>

//BNO_055
Adafruit_BNO055 bno = Adafruit_BNO055(55);

//Servo
Servo serd;
Servo sl1;
int poste = 90;
//Sensor Laser
float tiempo;

void setup() {
  serd.attach(6); // servo de direccion
  sl1.attach(9); // servo de laser
  /*
    definir rangos que no me acuerdo como hacerlo en arduino
  */
  Serial.begin(9600);
  serd.write(90);
  sl1.write(135);// el punto medio es 105
  Serial.println("Orientation Sensor Test"); Serial.println("");
  if (!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  bno.setExtCrystalUse(true);
  //bno_055(1);
  delay(500);

}

void loop() {
  int distl1; //
  int pos[6] = {135, 120, 90, 75, 90, 120}; // lo pongo asi para hacer un solo for
  int distl[6];

  //if (angle <= 360 && angle >= 0)
  bno_055(3.5);
  Serial.println("estoy aca");
  for (int i = 0; i <= 5; i++) {

    //Serial.println(angle);
    sl1.write(pos[i]);
    delay(800);
    tiempo = pulseIn(3, HIGH) / 100;
    //Serial.print("tiempo:\t");
    //Serial.println(tiempo);

    //distl[i] = tiempo;      //guardado de las 6 lecturas de izq. a der.
    //Serial.print(i);
    //Serial.print("     ");
    //Serial.println(distl[i]);
    //Serial.println();

    bno_055(3.5);

    if (tiempo < 30)
    {
      dist_45(i);
    }
  }
}
void dist_45(int i) // para cuando el laser detecta menos de 45cm
{
  Serial.println("entro");
  int pa = poste;
  if (i <= 1 || i == 5)
  {
    /* while (tiempo < 45 && pa > 20) //cambiar la condicion por la lectura del sensor??
      {
         //printf("se rompio aca1\n");
         //printf("posicion actual: %d\n",pa);
         tiempo = pulseIn(3, HIGH) / 100;
         pa-=20;
         Serial.print("funciona");
         Serial.println(pa);
         serd.write(pa);
      }*/
    while (tiempo < 30) {
      tiempo = pulseIn(3, HIGH) / 100;
      serd.write(20);

    }
    serd.write(poste);
  }
  else
  {
    /* while (tiempo < 45 && pa < 160) { //lo mismo aca??
         // printf("se rompio aca2\n");    //la direccion se mueve a la izquierda
         // printf("posicion actual: %d\n",pa);
         tiempo = pulseIn(3, HIGH) / 100;
         pa+=20;
         serd.write(pa);
      }*/
    while (tiempo < 30) {
      tiempo = pulseIn(3, HIGH) / 100;
      serd.write(140);

    }
    serd.write(poste);
  }
  //bno_055(3.5);
}
void bno_055(float multiplicador)
{
  sensors_event_t event;
  bno.getEvent(&event);
  int angle = event.orientation.x;
  poste = 90;
  Serial.print("Si me ejecuto....\t");

  Serial.print(angle);
  Serial.print("\t");
  if (angle > 180 && angle < 360)
  {
    poste -= (angle - 358) * 3.5; /////DERECHA
    serd.write(poste);
  }
  else
  {
    poste -= angle * 3.5; ////IZQUIERDA
    serd.write(poste);
  }
  Serial.println(poste);
}
