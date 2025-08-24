#include "ESP8266WiFi.h"
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 0;
const int valve_in = 5;
const int valve_out = 4;

const char* ssid = "hotspot";
const char* password = "password";
IPAddress local_IP(192,168,56,9);
IPAddress gateway(192,168,56,232);
IPAddress subnet(255,255,255,0);

WiFiServer server(80);


float average = 0;
int counter;
HX711 scale;

void setup() {
  Serial.begin(57600);
  
  WiFi.config(local_IP,gateway,subnet);
  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  server.begin();  
  Serial.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)
            
  scale.set_scale(-664);
  //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");

}

void loop() {
  WiFiClient client = server.available();
  if(!client){
    Serial.print("no connection");
  }
  
  
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  average = scale.get_units(10);
  Serial.println(average);
  if(average > 1000){
    digitalWrite(valve_in,0);
    digitalWrite(valve_out,1);
    counter++;
    while(average > 10);
  }
  digitalWrite(valve_in,1);
  digitalWrite(valve_out,0);
  delay(100);
  if(client.available()){
      String req = client.readStringUntil('\r');
      client.flush();
      String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n";
      response += "Cache-Control: no-cache\r\n\r\n";
      response += "<!DOCTYPE HTML><html><body>";
      response += "<meta http-equiv='refresh' content='1'>";
      response += "<h1>Sensor Value: ";
      response += average;
      response += "</h1>";
      response += "<h1>How many liters?: ";
      response += counter;
      response += "</h1></body></html>";

      client.print(response);
      client.stop();
  }
}
