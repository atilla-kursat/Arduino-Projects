long distance,duration;
void setup() {
pinMode(5,OUTPUT);
pinMode(7,INPUT);
pinMode(8,OUTPUT);
}

void loop() {

  int threshold = distancefunc();
  if (threshold < 7)
  digitalWrite(8,HIGH);
  else
  digitalWrite(8,LOW);
  }

  int distancefunc(){
  digitalWrite(5,LOW);
  delayMicroseconds(2);
  digitalWrite(5,HIGH);
  delayMicroseconds(10);
  digitalWrite(5,LOW);

  duration = pulseIn(7,HIGH);
  distance = duration/58.2;
  delayMicroseconds(50);

  return distance;
    
  }
