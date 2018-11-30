/*Wireless access point*/
#include <spi.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "Wap.h"

WiFiServer wapServer(80);

Wap::Wap(void)
{
  accessPointSSID ="mkr1000"
  if(WiFi.status() == WL_NO_SHIELD)
  {
    //No Hardware detected so we destruct this object.
    this-> ~Wap();
  }
  wapServer.begin();
}
Wap::~Wap(void){
  WiFi.end()
}
Wap::getCredentials() {
  WiFiClient client = server.available();
  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (currentLine.length() == 0) {
            //send HTML to client
            this-> sendHtml(client);
          }
          else {
             //check for data
            currentLine = "";
          }
        }
        else if (c != '\r') {
          currentLine +=c;
        }
      }
    }
    client.stop();
  }
}

Wap::printAPStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.print("signal strength (RSSI):");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
  Serial.print("To connect, open a browser to http://");
  Serial.println(ip);
}
