//2018/10/18 HT
#ifndef SERVOMOTOR_HPP_INCLUDED
#define SERVOMOTOR_HPP_INCLUDED


class ServoMotor{
	public:
		ServoMotor(float frequency,float baseDuty,float eigenDuty,int operatingAngle,int chanel,int pin);
		int setup();
		void offset(int revision_deg);
		void cycle();
		void giveDeg(float deg);
	private:
		//Pwm *m1;

		int revisionDeg;
		int operating_Angle;
		int deg;

		float eigen_Duty;
		float base_Duty;
		float frequency;
		float appendBase;

    int chanel;
    int pin;
};

#endif//SERVOMOTOR_HPP_INCLUDED
