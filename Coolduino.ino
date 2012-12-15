#include <IRremote.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int IRled=1;
int fanCtrl=3;
int tempPin=A0;
int IRpin=A1;
IRrecv irrecv(IRpin);
decode_results results;
int tempC=27;
int temp;
int IR;

void LCDprint(int Current,int Real) {
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(Current);
  lcd.setCursor(0,1);
  lcd.print("Limit:");
  lcd.print(Real);
  delay(100);
}

void setup() {
  lcd.begin(16,2);
  irrecv.enableIRIn();
  pinMode(IRled,OUTPUT);
  pinMode(fanCtrl,OUTPUT);
  digitalWrite(IRled,LOW);
}

void loop() {
  if (irrecv.decode(&results)) {
    digitalWrite(IRled,HIGH);
    IR=results.value;
    delay(50);
    irrecv.resume();
  }
  delay(10);
  digitalWrite(IRled,LOW);
  temp=analogRead(tempPin);
  temp=temp*400/1024;
  if(temp>tempC) {
    if(temp-tempC<10)
      analogWrite(fanCtrl,150);
    else if(temp-tempC<=20 && temp-tempC>=10)
      analogWrite(fanCtrl,200);
    else if(temp-tempC>20)
      analogWrite(fanCtrl,255);
  }
  switch(IR) {
    case 16754775:
      tempC=tempC+1;
      break;
    case 16769055:
      tempC=tempC-1;
      break;
  }
  LCDprint(temp,tempC);
}
