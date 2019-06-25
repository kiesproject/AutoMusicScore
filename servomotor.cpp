#include "servomotor.hpp"
#include "util.h"
#include <Arduino.h>

  ServoMotor::ServoMotor(float frequency,float baseDuty,float eigenDuty,int operatingAngle,int chanel,int pin){
	this->base_Duty=baseDuty;
	this->eigen_Duty=eigenDuty;
	this->operating_Angle=operatingAngle;
  this->chanel=chanel;
  this->pin=pin;

	//this->m1=m1;
	this->frequency=frequency;
	appendBase=0.0f;
	revisionDeg=0;
	deg=0;
}

int ServoMotor::setup(){
	int error;
  int chanel;
  //ledcSetup(チャンネル,周波数,PWMの範囲)
  ledcSetup(chanel,frequency,8);
  //ledcAttachPin(ピン番号,チャンネル)
  ledcAttachPin(pin,chanel);
	//error=m1->setupPwmOut(frequency,0);
	return error;
}

void ServoMotor::offset(int revision_deg){
	/*0�x�̈ʒu��C�ӂ̊p�x�����ړ������邱�Ƃ��ł��� */

	this->revisionDeg=revision_deg;
	appendBase=(eigen_Duty*revisionDeg);
}

void ServoMotor::cycle(){
	deg=floatlimit(-operating_Angle/2-revisionDeg,deg,operating_Angle/2-revisionDeg);
	ledcWrite(chanel,(base_Duty+appendBase)+(deg*eigen_Duty));
}

void ServoMotor::giveDeg(float deg){
	this->deg=deg;
}

/*����
//Sg90�p
#if 0
void ServoMotor::degree(float deg){

	deg=floatlimit(-90.0,deg,90.0);

	m1->pwmWrite(0.0725+(deg*0.00052777777));

}

#endif
//MG996R
#if 0
void ServoMotor::degree(float deg){

	deg=floatlimit(-90.0,deg,90.0);

	m1->pwmWrite(0.075+(deg*0.0005555555));

}
void ServoMotor::flag(int a){
	if(a==0) m1->pwmWrite(0.075);
	else if(a==-1) m1->pwmWrite(0.125);
	else if(a==1) m1->pwmWrite(0.025);
}
#endif
//LDX-227
#if 0
void ServoMotor::degree(float deg){

	deg=floatlimit(-135.0,deg,135.0);

	m1->pwmWrite(0.0725+(deg*0.00052777777));

}
void ServoMotor::flag(int a){
	if(a==0) m1->pwmWrite(0.0725);
	else if(a==-1) m1->pwmWrite(0.12);
	else if(a==1) m1->pwmWrite(0.025);
}
#endif
 */
