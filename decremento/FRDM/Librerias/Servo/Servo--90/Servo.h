#include "SoftwarePWM.h"

#define PERIOD 20000
#define ANGLE_MIN  -90
#define ANGLE_MAX	90
class Servo{

public:
	Servo(PinName pin_servo);
	void setLimits(int min_pulsewidth,int max_pulsewidth);
	void write(int degrees);
	void disable();
	void enable(int degrees);

private:
	SoftwarePWM softpwm;
	int min_pulse;
	int max_pulse;
	int imap(int x, int x1, int x2, int y1, int y2);

};
