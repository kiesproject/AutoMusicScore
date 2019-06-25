#include "servoLDX_227.hpp"
#include "servomotor.hpp"
#include "util.h"
#include <math.h>

//flortlimit 第2が入力する値,第1より下回れば第1で固定,第3より上回れば第3で固定
Servo::Servo(ServoMotor &sm):sm(sm){

	dtData=0.0f;    //微分時間
	targetPos=0.0f; //postion場所
	targetAcc=0.0f; //acceleration加速度
	targetVel=0.0f; //velocity速度
	limitVel=0;     //最大速度
	limitAcc=0;     //最大加速度
	relativeVel=0;  //相対速度
	relativeAcc=0.0f;//相対加速度

	returnOver=0.0f;//最大値
	returnUnder=0.0f;//最低値
	mode=0;

}

int Servo::setup(){
	int error;
	error+=sm.setup();
	return error;
}

void Servo::cycle(){

	integrator(); //積分
	sm.giveDeg(relativePos); //相対ポジションから角度を
	sm.cycle(); //再帰
}

void Servo::integrator(){

	if(mode==MODE_POS){
		float diffX=targetPos-relativePos; //求めているポジション-相対ポジション
		float  noHalfdownX=fsign(diffX)*sqrtf(2*targetAcc*fabsf(diffX)); //sin(ポジションの差)*√2*求めている加速度
		
		targetVel=fsign(diffX)*(sqrtf(2*targetAcc*fabsf(diffX))-dtData*targetAcc/2); //
		float lastVelocityX=diffX/dtData; //座標/時間=速度 ピッタリの
		targetVel=abs_min(lastVelocityX,targetVel);//上記2つどっちがいいかな

		if(targetVel*fsign(diffX)<0.0f){ //目標速度がマイナスになったら
			targetVel=abs_min(lastVelocityX,noHalfdownX);//最後の速度とnoHalfdownxを比較、良い方を取る
		}

		targetVel=floatlimit(-limitVel,targetVel,limitVel); //-∞~目標加速~∞
	}else if(mode==MODE_VEL){

	}else{
		targetVel=0.0f;
	}

	//�����x����p
	float oldVelocityX;
	oldVelocityX=relativeVel;//テンプする現在の速度

	float velocityUnderLimitX,velocityOverLimitX;//上限と下限

	if(targetVel-relativeVel>0.0f){//目標速度と相対速度の差が正
		velocityUnderLimitX=relativeVel-limitAcc*dtData;//速度-加速度*時間
		velocityOverLimitX=relativeVel+targetAcc*dtData;//速度+加速度*時間
	}else{//負
		velocityUnderLimitX=relativeVel-targetAcc*dtData;//相対速度-加速度*時間
		velocityOverLimitX=relativeVel-limitAcc*dtData;//相対速度-加速度*時間
	}
	//確定
	returnOver=velocityOverLimitX;
	returnUnder=velocityUnderLimitX;

	//���x������������
	float targetVelLimitX=floatlimit(velocityUnderLimitX,targetVel,velocityOverLimitX);
	targetVelLimitX=floatlimit(-limitVel,targetVel,limitVel);
	//���

	relativeVel = targetVelLimitX; //相対速度
	//���x�ω���������x�����߂đ��
	relativeAcc=(relativeVel - oldVelocityX) / dtData; //相対加速度
	//�ϕ����Ĉʒu���o��
	relativePos+=relativeVel*dtData; //相対変移

}
/*
void Servo::giveTargetPos(float tgPos){
	this->targetPos=tgPos;
}

void Servo::setTargetAcc(float tgAcc){
	this->targetAcc=tgAcc;
}

void Servo::setLimitVel(float limVel){
	this->limitVel=limVel;
}

void Servo::setLimitAcc(float limAcc){
	this->limitAcc=limAcc;
}

void Servo::setdtData(float dt){
	this->dtData=dt;
}
*/
/*
float Servo::reRelativeVel(){
	return relativeVel;
}
float Servo::reRelativePos(){
	return relativePos;
}
float Servo::reRelativeAcc(){
	return relativeAcc;
}

*/
