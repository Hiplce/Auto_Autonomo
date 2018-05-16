/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>
# include <Servo.h>

VL53L0X sensor;
Servo servoMotor;
uint16_t radio=0.0;
int horario[19];
int antihorario[19];
uint8_t dire = sensor.getAddress();

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  servoMotor.attach(9);
  sensor.init();
  sensor.setTimeout(500);
  servoMotor.write(0);

  
  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
 
}

void loop()
{
 
 
  Serial.print ("direccion:");
  Serial.println(dire);
  for (int i = 0; i <= 180;i=i+10)
  {
    // Desplazamos al ángulo correspondiente y leo sensor
    //servoMotor.write(i);
    radio=sensor.readRangeContinuousMillimeters();
    //horario[i]=float(radio);
    Serial .print("Radio: ");
    Serial.print(radio);
    Serial.print( "mm Angulo: ");
    Serial.print(i);
    Serial.print("Grados\n");
    //Serial.print(horario[i]);
    
    delay(50);
        }
 
  // Para el sentido negativo
 /* for (int i = 180; i > 0;i=i-10)
  {
    // Desplazamos al ángulo correspondiente
    //servoMotor.write(i);
    radio=sensor.readRangeContinuousMillimeters();
    //antihorario[i]=float(radio);
    Serial .print("Radio: ");
    Serial.print(radio);
    Serial.print( "mm Angulo: ");
    Serial.print(i);
    Serial.print("Grados\n");
    //Serial.print(antihorario[i]);
    //Serial.println(horario[i]);
    delay(50);
  }*/
  
  //Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println();
}


