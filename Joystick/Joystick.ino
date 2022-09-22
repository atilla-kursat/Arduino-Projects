int rawx=0;
int rawy=0;
int x=0;
int y=0;

void setup() {
Serial.begin(9600);
pinMode(7,OUTPUT);
pinMode(9,OUTPUT);
pinMode(11,OUTPUT);
pinMode(13,OUTPUT);

}

void loop() {
rawx= analogRead(A0);
x = map(rawx,0,1023,0,255);
Serial.println("x");
Serial.println(x);
if(x>=150){
  digitalWrite(7,HIGH);
  digitalWrite(9,LOW);
}
else if (x<110){
  digitalWrite(9,HIGH);
  digitalWrite(7,LOW);
}
else{
  digitalWrite(9,LOW);
  digitalWrite(7,LOW);
}
delay(100);
rawy= analogRead(A2);
y = map(rawy,0,1023,0,255);
Serial.println("y");
Serial.println(y);
if(y>=150){
  digitalWrite(11,HIGH);
  digitalWrite(13,LOW);
}
else if (y<110){
  digitalWrite(13,HIGH);
  digitalWrite(11,LOW);
}
else{
  digitalWrite(13,LOW);
  digitalWrite(11,LOW);
}
delay(100);


}
