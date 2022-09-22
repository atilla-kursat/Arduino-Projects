int rawx=0;
int rawy=0;
uint8_t packet[4]; 

void setup() {
Serial.begin(9600);
packet[0]= 0;
packet[3] = 8;

}

void loop() {
  rawx= analogRead(A0);
  packet[1] = map(rawx,0,1023,-127,127);
  rawy= analogRead(A2);
  packet[2] = map(rawy,0,1023,-127,127);

  Serial.write(packet,4);
  delay(10);
}
