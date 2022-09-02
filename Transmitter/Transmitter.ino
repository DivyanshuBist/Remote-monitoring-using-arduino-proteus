#include<VirtualWire.h>
const int trig1=13,echo1=12;
const int trig2=11,echo2=9;
const int trig3=8,echo3=7;
const int trig4=6,echo4=5;
void setup() {
  Serial.begin(9600);
  pinMode(trig1,OUTPUT);
  pinMode(echo1,INPUT);
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(A1);
  vw_setup(4000); 
}

void loop() {
  String str_msg;
  String condition;
   digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);      // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  int duration1 = pulseIn(echo1, HIGH);// Reads the echoPin, returns the sound wave travel time in microseconds
  int  distance1= duration1*0.034/2;

  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);      // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  int duration2 = pulseIn(echo2, HIGH);// Reads the echoPin, returns the sound wave travel time in microseconds
  int  distance2= duration2*0.034/2;
  
  digitalWrite(trig3, LOW);
  delayMicroseconds(2);
  digitalWrite(trig3, HIGH);      // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trig3, LOW);
  int duration3 = pulseIn(echo3, HIGH);// Reads the echoPin, returns the sound wave travel time in microseconds
  int  distance3= duration3*0.034/2;

  digitalWrite(trig4, LOW);
  delayMicroseconds(2);
  digitalWrite(trig4, HIGH);      // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trig4, LOW);
  int duration4 = pulseIn(echo4, HIGH);// Reads the echoPin, returns the sound wave travel time in microseconds
  int  distance4= duration4*0.034/2;
  
  Serial.print(distance1);
  Serial.print(" ");
  Serial.print(distance2);
  Serial.print(" ");
  Serial.print(distance3);
  Serial.print(" ");
  Serial.print(distance4);
  Serial.print(" ");
  if(distance1<100 or distance2<100 or distance3<100 or distance4<100) {
    condition="nearby  ,";
  }
  else{
    condition="isolated,";
  }
  Serial.println(condition);
  int sensor_LM35 = analogRead(A0);
  int temp = sensor_LM35 / 2;
  str_msg=condition+String(temp);
  const char *msg = str_msg.c_str();
  vw_send((uint8_t*)msg,strlen(msg));
  vw_wait_tx();
  delay(100);
}
