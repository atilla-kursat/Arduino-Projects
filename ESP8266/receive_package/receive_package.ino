#include "ESP8266WiFi.h"

const char* ssid = "wifi-name"; //Enter SSID
const char* password = "password"; //Enter Password
IPAddress staticIP(192, 168, 1, 55); // replace with desired IP address
IPAddress gateway(192, 168, 1, 1);    // replace with gateway IP address
IPAddress subnet(255, 255, 255, 0);   // replace with subnet mask

WiFiClient client;
WiFiServer server(80);

void setup(void)
{ 
  pinMode(16, OUTPUT);
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
   
  }

  server.begin();

}

void loop() 
{   client = server.available();
  
   if (client) { // replace IP address and port with the desired destination
    while (client.connected()) {
      if (client.available()) {
        String incomingData = client.readString();
        if (incomingData.length() > 0) {
          Serial.println(incomingData);
        }
      }
    }
    client.stop();
    
  } 





  
}
