volatile int interruptCounter1;
volatile int interruptCounter2;
hw_timer_t * timer1 = NULL;
hw_timer_t * timer2 = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


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
  timerAlarmWrite(timer1,1000000,true); //1秒に1回
  timerAlarmWrite(timer2,10000000,true); //10秒に1回
  timerAlarmEnable(timer1);
  timerAlarmEnable(timer2);

  //servo1
  ledcSetup(0,50,10);
  ledcAttachPin(23,0);
  ledcWrite(0,base_limit(45,0,105));
  //servo2
  ledcSetup(1,50,10);
  ledcAttachPin(22,1);
  ledcWrite(1,base_limit(50,0,100));
}

void loop() {
  // put your main code here, to run repeatedly:
  if (interruptCounter1 > 0) {
      portENTER_CRITICAL(&timerMux);
      interruptCounter1--;
      portEXIT_CRITICAL(&timerMux);
      /* ここから好きな関数を書き、好きな秒数で呼び出せる。 */
      servo();
    }
  if (interruptCounter2 > 0) {
      portENTER_CRITICAL(&timerMux);
      interruptCounter2--;
      portEXIT_CRITICAL(&timerMux);
      /* ここから好きな関数を書き、好きな秒数で呼び出せる。 */
      control();
    }
}

void servo(){
  //ledcWrite(使いたいモーター,duty)
  //base_limit(最低値,原点0から+-で整数を与える,最高値)
 ledcWrite(0,base_limit(45,0,105));
 ledcWrite(1,base_limit(50,0,100));
}

void control(){

}

//baseから+,-で調整する
int base_limit(int a,int duty,int c){
  return intlimit(a,75-duty,c);
}

//限界値で止める
int intlimit(int a,int duty,int c){
  if(duty > c){
    return c;
  }
  if(duty < a){
    return a;
  }
  return duty;
}
