#include "servoLDX_227.hpp"
#include "servomotor.hpp"
#include "util.h"

ServoMotor sm(50,0.75,0.000003,270,0,23);

//タイマー割り込みの準備
volatile int interruptCounter1;
volatile int interruptCounter2;
hw_timer_t * timer1 = NULL;
hw_timer_t * timer2 = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

//タイマーに必要な関数
void IRAM_ATTR onTimer1(){
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter1++;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void IRAM_ATTR onTimer2(){
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter2++;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //timerBegin(使用するタイマーの番号0~3,プリスケーラー 1マイクロ秒ごとなら80を指定,カウントアップ指定)
  timer1=timerBegin(0,80,true);
  timer2=timerBegin(1,80,true);
  timerAttachInterrupt(timer1, &onTimer1,true);
  timerAttachInterrupt(timer2, &onTimer2,true);
  //マイクロ秒を百万間隔で呼び出す。(1秒ごと)
  timerAlarmWrite(timer1,100000,true);
  timerAlarmWrite(timer2,1000000,true);
  timerAlarmEnable(timer1);
  timerAlarmEnable(timer2);
  sm.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (interruptCounter1 > 0) {
      portENTER_CRITICAL(&timerMux);
      interruptCounter1--;
      portEXIT_CRITICAL(&timerMux);
      /* ここから好きな関数を書き、好きな秒数で呼び出せる。 */
      cycle();
    }
  if (interruptCounter2 > 0) {
      portENTER_CRITICAL(&timerMux);
      interruptCounter2--;
      portEXIT_CRITICAL(&timerMux);
      /* ここから好きな関数を書き、好きな秒数で呼び出せる。 */
      giveDig_cycle();
    }
}

void cycle(){
  sm.cycle();
  Serial.println("cycle");
}

void giveDig_cycle(){
  sm.giveDeg(90.0);
  Serial.println("giveDeg");
}
