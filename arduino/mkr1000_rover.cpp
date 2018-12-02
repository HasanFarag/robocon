#include <SPI.h>
#include <WiFi101.h> //MKR WiFi 1010 Library
#include <WiFiUdp.h>
#include <RTCZero.h>
#include "secrets.h"

//Instantiate objects
RTCZero rtc;
WiFiServer server(80);

//Wifi Network Information - Needs to be made safer
char ssid[] = SECRET_SSID;
char password[] = SECRET_PASS;
int wifiStatus = WL_IDLE_STATUS;

bool rtcSet = false;
void setup() {
  //Start real time clock
  rtc.begin();
  //Establish Wifi Link
  if (WiFi.status() == WL_NO_SHIELD) {
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( wifiStatus != WL_CONNECTED) {
    wifiStatus = WiFi.begin(ssid, password);
    delay(10000);
  }
  //We need to check the rtc is up to date as soon as
  do {
    uint32_t ntpEpoch = WiFi.getTime();
    if(ntpEpoch > 0 && rtc.getEpoch() < ntpEpoch){
      rtc.setEpoch(WiFi.getTime());
      rtcSet = true;
    }
  }
  while(!rtcSet);

  server.begin();
  // you're connected now, so print out the status:
  //printWiFiStatus();
}

void loop() {
  // put your main code here, to run repeatedly:
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          //We need a cleaner way to do the html, css, js stuff
          //Otherwise the code will become unbearably long.
              
          // send a standard http response header
          const int GMT = 0;
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          //TODO: Put the webpage stuff in an html file then figure out how to pass data back and forth.
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          client.println("<style>");
          client.println("input[type=range][orient=vertical]");
          client.println("{writing-mode: bt-lr; /* IE */");
          client.println("-webkit-appearance: slider-vertical; /* WebKit */");
          client.println("width: 8px; height: 175px; padding: 0 5px;}");
          client.println("</style>");
          client.println("</head>");
          client.print("<h1>Rover Time: ");
          client.print(rtc.getDay());
          client.print("/");
          client.print(rtc.getMonth());
          client.print("/");
          client.print(rtc.getYear());
          client.print(" ");
          client.print(rtc.getHours() + GMT);
          client.print(":");
          client.print(rtc.getMinutes());
          client.print(":");
          client.print(rtc.getSeconds());
          client.println("</h1>");
          client.println("<input type='range' orient='vertical' id='speed-bar' min='-100' max = '100' value='0'>");
          client.println("<input type='range' orient='vertical' id='direction-bar' min='-100' max = '100' value='0'>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
  }
}
