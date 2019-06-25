  #ifndef SERVOLDX_227_HPP_INCLUDED
#define SERVOLDX_227_HPP_INCLUDED

#include "servomotor.hpp"


class Servo {
	public:
		Servo(ServoMotor &sm);
		int setup();
		void integrator();
		void cycle();
		void giveTargetPos(float tgPos){targetPos=tgPos,mode=MODE_POS;};
		void gibeTargetVel(float tgVel){targetVel=tgVel,mode=MODE_VEL;};

		void setTargetAcc(float tgAcc){targetAcc=tgAcc;};
		void setLimitVel(float limVel){limitVel=limVel;};
		void setLimitAcc(float limAcc){limitAcc=limAcc;};
		void setdtData(float dt){dtData=dt;};

		float reRelativeVel(){return relativeVel;};
		float reRelativePos(){return relativePos;};
		float reRelativeAcc(){return relativeAcc;};

	private:
		enum{
			MODE_NULL=0,
			MODE_POS,
			MODE_VEL,

		};
		int mode;

		//Pwm *m1;
		ServoMotor &sm;
		float targetPos;
		float targetAcc;
		float targetVel;

		float dtData;
		float relativeVel;
		float relativeAcc;
		float relativePos;
		float limitVel;
		float limitAcc;

		float returnOver;
		float returnUnder;
};


#endif//SERVOLDX_227_HPP_INCLUDED
