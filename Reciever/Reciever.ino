#include<VirtualWire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#define LED_PIN A1
//major project
void setup() {
  pinMode(LED_PIN,OUTPUT);
  lcd.begin(20,4); 
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(4);
  vw_setup(4000);
  Serial.begin(9600);
  vw_rx_start();

}

void loop() {
    int temp=0;
    String t="";
    String msg;
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen=VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen))
    {  
         String str_out = String((char*)buf);
         Serial.println(str_out);
//         calculation
         int i=0;
          for(i;i<str_out.length();i++){
            if(str_out[i]!=','){
              msg+=str_out[i];
            }
            else break;
          }
          i++;
          for(i;str_out[i]-'0'!=-44;i++){
              temp=temp*10;
              temp+=(str_out[i]-'0');
              t+=str_out[i];
          }
          //lcd display

          lcd.setCursor(0,0);
          lcd.print(msg);
          lcd.setCursor(0,1);
          lcd.print("Temperature:");
          lcd.setCursor(0,2);
          lcd.print(temp);

    }
    if(temp>=38){
      digitalWrite(LED_PIN,HIGH);
     }
     else{
      digitalWrite(LED_PIN,LOW);
     }
  delay(100);
}
