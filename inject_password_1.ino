#include <HijelHID_BLEKeyboard.h>
const int push = 4;
HijelHID_BLEKeyboard keyb("cheap keyb");


void setup() {
  pinMode(push, INPUT_PULLUP);
  keyb.begin();

}

void loop() {
  if (keyb.isConnected()){
    if (digitalRead(push) == LOW){
      keyb.print("Misnooplogg\"1");

      while(digitalRead(push) == LOW){
        delay(10);
      }
        
      
    }
  }
  delay(10);
}
