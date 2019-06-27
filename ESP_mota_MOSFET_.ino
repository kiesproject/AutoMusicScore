#define FET  25
#define sw  23
bool flag = 0;
bool skip = 0;
void setup(){
  Serial.begin( 9600 );
  pinMode( FET, OUTPUT); //信号用ピン
   pinMode( sw, INPUT_PULLUP);
}



void loop(){
  Serial.println(digitalRead(sw));
  if((digitalRead(sw) ^ flag) == 1 && skip == 0){
    flag = !flag;
    skip = 1;
    Serial.println("HIGH");
    digitalWrite(FET, HIGH);
    delay(900);
  }else{
    if ((digitalRead(sw) ^ flag) == 0 && skip == 1) skip = 0;
    Serial.println("LOW");
    digitalWrite(FET, LOW);
  }
  delay(100);

}
