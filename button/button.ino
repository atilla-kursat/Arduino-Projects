
int switch_state = 0;
int token = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(8,INPUT);
pinMode(10,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch_state = digitalRead(8);
  if(switch_state == 1){
    if (token==1){
      digitalWrite(10,LOW);
      token=0;
      }
  else if (token==0){ 
  digitalWrite(10,HIGH);
  token=1;
  }
  }
  if(switch_state == 0){
  if (token==1)
  digitalWrite(10,HIGH);
  if (token==0)
  digitalWrite(10,LOW);
  }
  }
  
