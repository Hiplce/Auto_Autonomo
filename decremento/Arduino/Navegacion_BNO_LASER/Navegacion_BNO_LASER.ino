#include <Wire.h> //bno y LCD
#include <Adafruit_Sensor.h> //bno
#include <Adafruit_BNO055.h> //bno
#include <utility/imumaths.h> //bno
#include <Servo.h>
#include <LiquidCrystal.h> //LCD
//BNO_055
Adafruit_BNO055 bno = Adafruit_BNO055(55);

//LCD
LiquidCrystal lcd(11, 13, 10);
unsigned long tiempo;
float reset = 0;
String b1, b2, v;

//Servo
Servo serd;
Servo sl1;
int pos = 90;
//Sensor Laser
float tiempo;

void setup() {
  Serial.begin(9600);

  serd.attach(6); // servo de direccion
  sl1.attach(9); // servo de laser

  //inicialización de servos
  serd.write(90);
  sl1.write(180);

  //declaración de pines LCD
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  lcd.begin(8, 2); //especificación de tamaño de LCD
  lcd.setBacklight(HIGH); //prender led del LCD
  /*
    definir rangos que no me acuerdo como hacerlo en arduino
  */
  //testeo de bno
  Serial.println("Orientation Sensor Test"); Serial.println("");
  if (!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  bno.setExtCrystalUse(true);
  bno_055(1);
  delay(500);

}

void loop() {
  tiempo = millis();
  int distl1; //
  int pos[10] = {180, 150, 120, 60, 30, 10, 30, 60, 120, 150}; // lo pongo asi para hacer un solo for
  int distl[10];
  bno_055(3.5);
  if ((tiempo - reset) < 1500)
  {
    v = analogRead(16) / 202.38;
    imp_lcd("V:  ", 0, 0);
    imp_lcd(v, 4, 0);
    if (bat == -1 || bat == 0)
    {
      b1 = (100.0 - ((4.6 - ((analogRead(14) / 1039.0) * 5.0)) * 250.0));
      imp_lcd("B1: ", 0, 1);
      imp_lcd(b1, 4, 1);
      bat++;
    }
    else
    {
      b2 = (100.0 - ((4.6 - ((analogRead(15) / 1039.0) * 5.0)) * 250.0)); //0.367
      imp_lcd("B2: ", 0, 1);
      imp_lcd(b2, 4, 1);
      bat++;
      if(bat == 3)
      {
        bat = -1;
      }
    }
    reset = millis();
  }
  for (int i = 0; i <= 9; i++) {
    sl1.write(pos[i]);
    //sl1.write(90);
    delay(200); //////////////////////////////////////////////////////////////¡¡¡¡¡¡¡ ver el tiempo que TARDA en tomar la medida !!!!!!!!////////////////////////////////////////////////////////
    tiempo = pulseIn(3, HIGH) / 100;
    distl[i] = tiempo;      //guardado de las 6 lecturas de izq. a der.
    //Serial.print(i);
    //Serial.print("     ");
    //Serial.println(distl[i]);
    //Serial.println();
    bno_055(3.5);
    if (distl[i] < 45)
    {
      dist_45(i);
    }
  }
}
void dist_45(int i) // para cuando el laser detecta menos de 45cm
{
  int pa = pos;
  if (i <= 2 || i >= 8)
  {
    while (tiempo < 45 && pa > 20) //cambiar la condicion por la lectura del sensor??
    {
      //printf("se rompio aca1\n");
      //printf("posicion actual: %d\n",pa);
      tiempo = pulseIn(3, HIGH) / 100;
      pa--;
      serd.write(pa);
    }
    serd.write(pos);
  }
  else
  {
    while (tiempo < 45 && pa < 160) { //lo mismo aca??
      // printf("se rompio aca2\n");    //la direccion se mueve a la izquierda
      // printf("posicion actual: %d\n",pa);
      tiempo = pulseIn(3, HIGH) / 100;
      pa++;
      serd.write(pa);
    }
    serd.write(pos);
  }
  bno_055(3.5);
}
void bno_055(float multiplicador)
{
  pos = 90;
  Serial.print("Si me ejecuto....\t");
  sensors_event_t event;
  bno.getEvent(&event);
  int angle = event.orientation.x;
  Serial.print(angle);
  Serial.print("\t");
  if (angle > 180 && angle < 360)
  {
    pos -= (angle - 360) * 3.5; /////DERECHA
    serd.write(pos);
  }
  else
  {
    pos -= angle * 3.5; ////IZQUIERDA
    serd.write(pos);
  }
  Serial.println(pos);
}



