#include "hcsr04.h"
#include "mbed.h"
//*HCSR04.cpp
HCSR04::HCSR04(PinName t, PinName e) : trig(t), echo(e) {}

long HCSR04::echo_duration() {
  timer.reset();  //reset timer
  max.reset();
  trig=0;   // trigger low
  wait_us(2); //  wait
  trig=1;   //  trigger high
  wait_us(10);
  trig=0;  // trigger low
  max.start();
  while(!echo){ // start pulseIN
    if(max.read_us() > 12000){
      max.stop();
      return 0;
    }
  }
  timer.start();
  while(echo){
    if(max.read_us() > 12000){
      max.stop();
      return 0;
    }
  }
  timer.stop();

  return timer.read_us();

}

long HCSR04::distance(){ //return distance in cm
  duration = echo_duration();
  distance_cm = (duration/2)/29.1  ;
  return distance_cm;
}