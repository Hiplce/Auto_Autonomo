#include <DCMotor.h>
#include <NewPing.h>
DCMotor motor_izq(M0_EN,M0_D0,M0_D1,false);
DCMotor motor_der(M1_EN,M1_D0,M1_D1);
#define vel(a) motor_izq.setSpeed(a);motor_der.setSpeed(a);

NewPing ultra_der (15,15,200);
NewPing ultra_del (16,16,200);
NewPing ultra_tra (19,19,200);
float dist_der;
float dist_del;
float dist_tra;
int velocidad;
int luz = 130;
#define f 6
#define e 5
#define g 11
#define h 10
#define p(a,b,c) analogWrite(a,c);analogWrite(b,c);
#define l(z,x,y) digitalWrite(z,y);digitalWrite(x,y);
void setup()
{
  //pinMode(14, INPUT); 
  Serial.begin(9600);
  pinMode(f,OUTPUT);
  pinMode(e,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(h,OUTPUT);
  delay(1000);
  p(f,e,luz);
}
void loop()
{
  d_prom();
  if(dist_del > 100 || dist_del < 10)
  {
   vel(100); 
   l(g,h,0);
   p(f,e,luz);
  }
  else if(dist_del < 20)
  {
    vel(-3);
    p(f,e,255);
    l(g,h,1);
    //while(true){}
  }
  else
  {
  velocidad = dist_del + 5;
  vel(velocidad);
  p(f,e,luz);
  l(g,h,0);
  delay(700);
  }
}


void d_der()
{
  float prom_der = 0;

  for(int i=1;i<=5;i++)
  {
    dist_der = ultra_der.ping_cm();
    Serial.println(dist_der);
    prom_der += dist_der;
    delay(20);
  }
  Serial.println();
  //dist_der = prom_der/5;
  dist_der = prom_der/5;
  return;
}
void d_del()
{
  float prom_del = 0;

  for(int j=1;j<=4;j++)
  {
    dist_del = ultra_del.ping_cm();
    Serial.println(dist_del);
    prom_del += dist_del;
    delay(30);
  }
  Serial.println();
  //dist_der = prom_der/5;
  dist_del = prom_del/4;
  return;
}
void d_tra()
{
  float prom_tra = 0;

  for(int k=1;k<=5;k++)
  {
    dist_tra = ultra_tra.ping_cm();
    Serial.println(dist_tra);
    prom_tra += dist_tra;
    delay(20);
  }
  Serial.println();
  //dist_der = prom_der/5;
  dist_tra = prom_tra/5;
  return;
}


////////////////////////////////////////////////////////
void d_prom()
{
  float dist_t = 0;
  int cont = 0;
  for(int i = 0;i <= 7;i++)
  {
  dist_der = ultra_der.ping_cm();
  delay(15);
  dist_del = ultra_del.ping_cm();
  delay(15);
  if(abs(dist_del - dist_der) < 5)
  {
    dist_t += dist_del + dist_der;
    cont += 2;
  }
  }
  dist_del = dist_t/cont;
}

