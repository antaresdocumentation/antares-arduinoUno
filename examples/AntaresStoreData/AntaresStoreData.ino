#include "AntaresArduinoUno.h"

String ACCESSKEY = "e7e349fc2216941a:9d0cf82c25277bdd";

String projectName = "DemoAntares";
String deviceName = "ArduinoEthernetShieldHttp";

Antares antares(ACCESSKEY);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
String URI="/~/antares-cse/antares-id/DemoAntares/ArduinoEthernetShieldHttp";
char server[] = "platform.antares.id";    // name address for Google (using DNS)
void setup() {
    Serial.begin(115200);
    antares.setDebug(true);
    Serial.println("connecting...");
    if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    // Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  
  //antares.connect();

  // if you get a connection, report back via serial:
  if (antares.client.connect(server, 8080)) {
    Serial.println("connected");
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}


void loop() {
   if(antares.client.connected())
{
  // Make your API request:
String  body="{";
          body+="  \"m2m:cin\": {";
          body+="    \"cnf\": \"message\",";
          body+="    \"con\": \"";
          body+="      {";
          body+="        \\\"status\\\": \\\"20\\\",";
          body+="         \\\"dim\\\": \\\"130\\\"";
          body+="      }";
          body+="    \"";
          body+="  }";
          body+="}";


    antares.client.print("POST " + URI + " HTTP/1.1\n");
    antares.client.print("Host: platform.antares.id:8080\n");
    antares.client.print("Connection: close\n");
    antares.client.print("X-M2M-Origin: " + ACCESSKEY + "\n");
    antares.client.print("Content-Type: application/json;ty=4\n");
    antares.client.print("Content-Length: "+String(body.length())+"\n");
    //client.print(body.length());
    antares.client.print("Cache-Control: no-cache\n");
    antares.client.print("\n");
    antares.client.print(body);
    antares.client.print("\n");
     while(antares.client.available()) {
    char c = antares.client.read();
    Serial.print(c);
  }
  delay(10000);
  } 

  if(!antares.client.connected()) {
    Serial.println("disconnected.");
    Serial.print("Reconnecting..");
    antares.client.stop();
    while(!antares.client.connect(server, 8080))
    {
      Serial.print(".");
      delay(100);
    }
  }
   
}

 
