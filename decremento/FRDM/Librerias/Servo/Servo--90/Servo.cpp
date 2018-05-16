#include "Servo.h"

Servo::Servo(PinName pin_servo):softpwm(pin_servo){

}

void Servo::enable(int degrees){
 softpwm.Enable(imap(degrees,ANGLE_MIN,ANGLE_MAX,this->min_pulse,this->max_pulse),PERIOD);
}

void Servo::disable(){
	softpwm.Disable();
}

void Servo::setLimits(int min_pulsewidth,int max_pulsewidth){
	this->min_pulse = min_pulsewidth;
	this->max_pulse = max_pulsewidth;
}

void Servo::write(int degrees){

	softpwm.SetPosition(imap(degrees,ANGLE_MIN,ANGLE_MAX,this->min_pulse,this->max_pulse));

}

int Servo::imap(int x, int x1, int x2, int y1, int y2) {

	int y;

	y = ((y2 - y1) / (x2 - x1)) * (x - x1) + y1;

	return y;
}
