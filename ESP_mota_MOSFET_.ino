const int FET6 = 25;
const int FET8 = 26; 
const int FET2 = 15;
const int FET4 = 14; 

void setup(){
  Serial.begin( 9600 );
  pinMode( motor6, OUTPUT); //信号用ピン
  pinMode( motor8, OUTPUT); //信号用ピン
  pinMode( motor2, OUTPUT); //信号用ピン
  pinMode( motor4, OUTPUT); //信号用ピン

  ledcSetup(0,12800,8); 
  ledcAttachPin(FET6,0);
  ledcAttachPin(FET8,0);
}

void forward(int speed) {         //正転
  ledcWrite (FET6, 1023-speed);   // on
  digitalWrite(FET8, HIGH);       // off
  digitalWrite(FET2, LOW);        // off
  digitalWrite(FET4, HIGH);       // on
}

void back(int speed) {            //逆転
  digitalWrite(FET6, HIGH);       // off
  analogWrite (FET8, 1023-speed); // on
  digitalWrite(FET2, HIGH);       // on
  digitalWrite(FET4, LOW);        // off
}

void stop() {
  digitalWrite(FET6, HIGH);  // off
  digitalWrite(FET8, HIGH);  // off
  digitalWrite(FET2, LOW);   // off
  digitalWrite(FET4, LOW);   // off
}

void brake() {
  digitalWrite(FET6, HIGH);  // off
  digitalWrite(FET8, HIGH);  // off
  digitalWrite(FET2, HIGH);  // on
  digitalWrite(FET4, HIGH);  // on
}

void loop(){
   int sp = 1024;
   forward(sp);
   delay(1000);
   stop();
   delay(1000);
}
