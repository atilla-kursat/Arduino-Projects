int i;
int switch_state=0;
void setup() {
pinMode(2,OUTPUT);
pinMode(6,OUTPUT);
pinMode(4,OUTPUT);
pinMode(10,INPUT);
}

void loop() {

switch_state= digitalRead(10);

if(switch_state == 1){  
for(i=2;i<=6;i+=2){
  digitalWrite(i,HIGH);
  delay(500);
  if (i>=6){
    for(i=2;i<=6;i+=2)
      {
        digitalWrite(i,LOW);
        delay(500);
      }
  }
}
}
  }
  
