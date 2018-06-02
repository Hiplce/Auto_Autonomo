#include "mbed.h"
#include "Servo.h"
#include "SoftwarePWM.h"
 Servo myservo (PTD1);
 
 int main() {
     myservo.setLimits(500,2400);
     myservo.enable(-90);
     /*
     while(1) {
         for(int i=180; i>0; i--) {
             myservo = i/100.0;
             wait(0.1);
         }
         for(int i=0; i<180; i++) {
             myservo = i/100.0;
             wait(0.1);
         }
     }
     */
     while(1){
     myservo.write(-100);
     wait(0.5f);
     myservo.write(0);
     wait(0.5f);
     myservo.write(90);
     wait(0.5f);
     myservo.write(0);
     wait(0.5f);
     }
 }