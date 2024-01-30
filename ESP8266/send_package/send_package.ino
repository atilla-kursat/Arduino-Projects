#include <ESP8266WiFi.h>

const char* ssid = "wifi-name";
const char* password = "password";
IPAddress staticIP(192, 168, 1, 53); // replace with desired IP address
IPAddress gateway(192, 168, 1, 1);    // replace with gateway IP address
IPAddress subnet(255, 255, 255, 0);   // replace with subnet mask
const char* destinationIP = "192.168.1.54"; // Replace with the destination IP address
const int destinationPort = 80; // Replace with the destination port

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.config(staticIP,gateway,subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    
  }
  
}

void loop() {
  if (Serial.available()) {
    if (client.connect(destinationIP, destinationPort)) {
      String incomingData = Serial.readString();
      client.print(incomingData);
      client.stop();
    } else {
    }
  }
}
