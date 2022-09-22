int rawx=0;
int rawy=0;
int x=0;
int y=0;
int i=8;
int j=0;
int ri=0;
int rj=0;

#include<LiquidCrystal.h>
#include<time.h>
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
Serial.begin(9600);
lcd.begin(16,2);
  ri=random(0,15);
  rj=random(0,1);
}

void loop() {
  delay(100);
  lcd.clear();
if(i==ri && j==rj){  
lcd.setCursor(i,j);
lcd.print("*");
  ri=random(0,16);
  rj=random(0,2);
}
else{
  lcd.setCursor(i,j);
lcd.print("*");
lcd.setCursor(ri,rj);
lcd.print("$");
}
rawx= analogRead(A0);
x = map(rawx,0,1023,0,255);
Serial.println("x");
Serial.println(x);
if(x>=150){
  if(i==0)
  i=15;
  else
  i--;
 
}
else if (x<110){
   if(i==15)
    i=0;
    else
    i++;

}

rawy= analogRead(A2);
y = map(rawy,0,1023,0,255);
Serial.println("y");
Serial.println(y);
if(y>=150){

    if(j<1)
    j++;
}
else if (y<110){

  if(j>0)
  j--;
}

}
