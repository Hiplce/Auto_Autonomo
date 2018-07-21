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
unsigned long t;
float reset = 0;
String b1, b2, v;
int bat = -1;
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
  delay(5000);
  sl1.write(125);

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
  t = millis();
  int distl1;
  int post[6] = {125, 110, 100, 85, 100, 110}; // lo pongo asi para hacer un solo for
  int distl[6];
  bno_055(3.5);
  //////////////////////////////Impresión LCD
  if ((t - reset) < 1500)
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
      if (bat == 3)
      {
        bat = -1;
      }
    }
    reset = millis();
  }
  /////////////////////////////Fin Impresión LCD
  
  /////////////////////////////Comienzo Navegación
  for (int i = 0; i <= 5; i++) {
    sl1.write(post[i]);
    //sl1.write(90);
    delay(200);
    tiempo = pulseIn(3, HIGH) / 100;
    distl[i] = tiempo;      //guardado de las 6 lecturas de izq. a der.
    //Serial.print(i);
    //Serial.print("     ");
    //Serial.println(distl[i]);
    //Serial.println();
    bno_055(3.5);
    if (distl[i] < 40)
    {
      dist_40(i);
    }
  }
  ////////////////////////////Fin Navegación
}
void dist_40(int i) // para cuando el laser detecta menos de 45cm
{
  if (i <= 1 || i == 5)
  {
    while (tiempo < 40) //cambiar la condicion por la lectura del sensor??
    {
      //printf("se rompio aca1\n");
      //printf("posicion actual: %d\n",pa);
      tiempo = pulseIn(3, HIGH) / 100;
      serd.write(20);
    }
    serd.write(pos-30);
    delay(20);
    serd.write(pos);
  }
  else
  {
    while (tiempo < 40) { //lo mismo aca??
      // printf("se rompio aca2\n");    //la direccion se mueve a la izquierda
      // printf("posicion actual: %d\n",pa);
      tiempo = pulseIn(3, HIGH) / 100;
      serd.write(140);
    }
    serd.write(pos+30);
    delay(20);
    serd.write(pos);
  }
  bno_055(3.5);
}

void bno_055(float multiplicador)//función para corregir con bno
{
  pos = 90;
  Serial.print("Si me ejecuto....\t");
  sensors_event_t event;
  bno.getEvent(&event);
  int angle = event.orientation.x;
  Serial.print(angle);
  Serial.print("\t");
  if (angle > 180 && angle < 358)
  {
    pos -= (angle - 360) * 2.5; /////DERECHA
    if (pos > 165)//si se pasan los 165 grados la rueda se traba con la estructura
    {
      serd.write(165);
      //Serial.print("lim  ");
    }
    else
    {
      serd.write(pos);
    }
  }
  else if (angle > 0 && angle <= 180)
  {
    pos -= (angle) * 2.5; ////IZQUIERDA
    if (pos < 20)//si se pasan los 20 grados la rueda se traba con la estructura
    {
      serd.write(20);
      //Serial.print("lim  ");
    }
    else
    {
      serd.write(pos);
    }
  }
  else
  {
    serd.write(pos);
  }
  //Serial.println(pos);
}

void imp_lcd(String palabra, int x, int y)//función para imprimir por LCD
{
  for (int i = 0; i < 4; i++)
  {
    lcd.setCursor(i + x, y);
    lcd.print(palabra[i]);
  }
}


