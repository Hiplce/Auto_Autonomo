#include <Servo.h>
#include <NewPing.h>
Servo servo;
char algo;

NewPing ultra_del1 (10,10,200);
NewPing ultra_del (7,7,200);
float dist_del1;
float dist_del;
float dist_tra;
int velocidad;

#define pwm 9
#define at 11
#define ad 10
int der = 180;
int izq = 0;
void setup()
{
  Serial.begin(115200);
  servo.attach(6);
  pinMode(pwm, OUTPUT);
  pinMode(at, OUTPUT);
  pinMode(ad, OUTPUT);
}
void loop()
{
  if (Serial.available() > 0) //pregunto si hay algo en el buffer
  {
    algo = Serial.read();//guardo en la variable algo lo que este en el buffer
    Serial.println(algo);
    if (algo == 'F') //ATRAS
    {
      while (algo == 'F')
      {
        algo = Serial.read();
        vel(255);
      }
    }
    if (algo == 'B') //ATRAS
    {
      while (algo == 'B')
      {
        algo = Serial.read();
        vel(-255);
      }
    }
    if (algo == 'I') //IZQ AVANCE
    {
      servo.write(izq);
      //delay(100);
      while (algo == 'I')
      {
        algo = Serial.read();
        vel(200);
      }
    }
    if (algo == 'J') //IZQ ATRAS
    {
      servo.write(izq);
      //delay(100);
      while (algo == 'J')
      {
        algo = Serial.read();
        vel(-200);
      }
    }
    if (algo == 'G') //DER AVANCE
    {
      servo.write(der);
      while (algo == 'G')
      {
        algo = Serial.read();
        vel(200);
      }
    }
    if (algo == 'H') //DER ATRAS
    {
      servo.write(der);
      while (algo == 'H')
      {
        algo = Serial.read();
        vel(-200);
      }
    }
    if (algo == 'R')
    {
      servo.write(izq);
      while (algo == 'R')
      {
        algo = Serial.read();
      }
    }
    if (algo == 'L')
    {
      servo.write(der);
      while (algo == 'L')
      {
        algo = Serial.read();
      }
    }
    if (algo == 'S') //RUEDAS RECTAS, PARADO
    {
      servo.write(95);
      servo.write(85);
      servo.write(90);
      while (algo == 'S')
      {
        algo = Serial.read();
        vel(0);
      }
    }
  }
}

void d_prom()
{
  float dist_t = 0;
  int cont = 0;
  for (int i = 0; i <= 7; i++)
  {
    dist_del1 = ultra_del1.ping_cm();
    delay(15);
    dist_del = ultra_del.ping_cm();
    delay(15);
    if (abs(dist_del - dist_del1) < 5)
    {
      dist_t += dist_del + dist_del1;
      cont += 2;
    }
  }
  dist_del = dist_t / cont;
}

void vel(int pot)
{
  if (pot > 0)
  {
    digitalWrite(at, 0);
    digitalWrite(ad, 1);
  }
  else
  {
    digitalWrite(at, 1);
    digitalWrite(ad, 0);
    pot = abs(pot);
  }
  analogWrite(pwm, pot);
}
