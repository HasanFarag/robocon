#include <SPI.h>
#include <WiFi101.h>
#include "Wireless.h"

WiFiServer server(80);

Wireless::Wireless(){
  //apssid[] = "MKR1000AP";
  status = WL_IDLE_STATUS;
  password = "";
  network = "";
  HTTP_req;
  readingNetwork = false;
  readingPassword = false;
  WiFiConnected = false;
}
boolean Wireless::isConnected(void){
  return WiFiConnected;
}
boolean Wireless::hasCredentials(void){
  if (network == "" or password == ""){
    return false;
  }
  else {return true;}
}
void Wireless::accessPoint(void){
  if(Serial){
    Serial.println("Access Point Web Server");
  }
  if (WiFi.status() == WL_NO_SHIELD) {
    if(Serial){
      Serial.println("WiFi shield not present");
    }
    while (true);
  }
  if(Serial){
    Serial.print("Creating access point named: ");
    Serial.println(apssid);
  }
  if (WiFi.beginAP(apssid) != WL_AP_LISTENING) {
    if(Serial){
      Serial.println("Creating access point failed");
    }
    while (true);
  }

  delay(1000);
  server.begin();
  if(Serial){
    printAPStatus();
  }
}

void Wireless::wifiCredentials(void) {
  WiFiClient client = server.available();
  if (client) {
    if(Serial){
      Serial.println("new client");
    }
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if(Serial){
          Serial.print(c);
        }
        if (c=='?') readingNetwork = true;
        if (readingNetwork) {
          if (c=='!') {
            network.replace("%20"," ");
            readingPassword = true;
            readingNetwork = false;
          }
          else if (c!='?') {
            network += c;
          }
        }
        if (readingPassword) {
          if (c==',') {
            if(Serial){
              Serial.println();
              Serial.print("Network Name: ");
              Serial.println(network);
              Serial.print("Password: ");
              Serial.println(password);
              Serial.println();
            }
            client.stop();
            WiFi.end();
            readingPassword = false;
          }
          else if (c!='!') {
            password += c;
          }
        }
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<html>");
            client.println("<head>");
            client.println("<style type=\"text/css\"> body {font-family: sans-serif; margin:50px; padding:20px; line-height: 250% } </style>");
            client.println("<title>Arduino Setup</title>");
            client.println("</head>");
            client.println("<body>");

            client.println("<h2>WIFI CREDENTIALS</h2>");
            client.print("NETWORK NAME: ");
            client.print("<input id=\"network\"/><br>");
            client.print("PASSWORD: ");
            client.print("<input id=\"password\"/><br>");
            client.print("<br>");

            client.print("<button type=\"button\" onclick=\"SendText()\">Enter</button>");
            client.println("</body>");
            client.println("<script>");
            client.println("var network = document.querySelector('#network');");
            client.println("var password = document.querySelector('#password');");

            client.println("function SendText() {");
            client.println("nocache=\"&nocache=\" + Math.random() * 1000000;");
            client.println("var request =new XMLHttpRequest();");
            client.println("netText = \"&txt=\" + \"?\" + network.value + \"!\" + password.value + \",&end=end\";");
            client.println("request.open(\"GET\", \"ajax_inputs\" + netText + nocache, true);");
            client.println("request.send(null)");
            client.println("network.value=''");
            client.println("password.value=''}");
            client.println("</script>");
            client.println("</html>");
            client.println();
            break;
          }
          else {
            currentLine = "";
          }
        }
        else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    if(Serial){
      Serial.println("client disconnected");
      Serial.println();
    }
  }
}

void Wireless::connectWifi(void) {
  if (network == "" or password == "") {
    if(Serial){
      Serial.println("Invalid WiFi credentials");
    }
        while (true);
  }
  while (WiFi.status() != WL_CONNECTED) {
    if(Serial){
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(network);
    }
    WiFi.begin(network, password);
    delay(10000);
  }
  if(Serial){
    Serial.println("WiFi connection successful");
    printWiFiStatus();
  }
  WiFiConnected = true;
  delay(1000);
}

void Wireless::printWiFiStatus(void) {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.print("signal strength (RSSI):");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void Wireless::printAPStatus(void) {
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
