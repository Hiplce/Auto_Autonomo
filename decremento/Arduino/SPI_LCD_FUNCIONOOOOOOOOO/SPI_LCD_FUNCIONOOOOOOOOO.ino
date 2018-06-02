#include <Wire.h>
#include <LiquidCrystal.h>


/////DATOS

//5 pulsos por vuelta de rueda
//diametro = 7,7 cm
//radio = 3,35 cm
//perimetro rueda = 24,19cm
//1 vuelta --> 5 pulsos
//5 ciclos / 1 segundo = 5Hz
//1 vuelta --> 1 segundo
//24,19 cm / 1 seg
// Connect via SPI. Data pin is #11, Clock is #13 and Latch is #10
LiquidCrystal lcd(11, 13, 10);
unsigned long tiempo;
float reset = 0;
String b1, b2, v;
int bat = -1;
void setup() {
  Serial.begin(9600);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  lcd.begin(8, 2);
  //lcd.print(hola[3]);
  //lcd.setCursor(0,1);
  lcd.setBacklight(HIGH);
}

void loop() {
  tiempo = millis();
  if ((tiempo - reset) < 1500)
  {
    v = analogRead(16)/202.38;
    imp_lcd("V:  ", 0, 0);
    imp_lcd(v, 4, 0);
    if (bat == true)
    {
      b1 = (100.0-((4.6-((analogRead(14)/1039.0)*5.0))*250.0));
      imp_lcd("B1: ", 0, 1);
      imp_lcd(b1, 4, 1);
      bat = false;
    }
    else
    {
      b2 = (100.0-((4.6-((analogRead(15)/1039.0)*5.0))*250.0));//0.367
      imp_lcd("B2: ", 0, 1);
      imp_lcd(b2, 4, 1);
      bat = true;
    }
    reset = millis();
  }
  Serial.print((100.0-((4.6-((analogRead(15)/1039.0)*5.0))*250.0)));
  Serial.print("\t");
  Serial.print(b2);
  Serial.println();
  delay(800);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis()/1000);
}
void imp_lcd(String palabra, int x, int y)//solo tengo que imprimir 3 posiciones
{
  for (int i = 3; i >= 0; i--)
  {
    lcd.setCursor(i + x, y);
    lcd.print(palabra[i]);
  }
}

