//#include <Servo.h>
//#include "Adafruit_VL53L0X.h"

//Adafruit_VL53L0X lox = Adafruit_VL53L0X();
// Direccion

//Servo
//Servo serd;
//Servo sl1;

unsigned long t1;
unsigned long t2;
float tiempo;
void setup() {
  Serial.begin(9600);
}
void loop() {
 tiempo = pulseIn(3,HIGH); //digitalPinToInterrupt(<pin_digital>); --> esto nos devuelve el ordinal del pin digital, solo se pueden usar el 2 y 3 digitales
  Serial.print((tiempo / 100));
  Serial.print("\n\r");
  delay(50);
}
