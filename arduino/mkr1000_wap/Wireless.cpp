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
  server.begin();
  //delay(1000);
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

RoverControl::RoverControl(){
  mazeMode = false;
  remoteMode = false;
  readingCommand =false;
  readString = "";

}
boolean RoverControl::isNone(void){
  if(!mazeMode or !remoteMode){
    return true;
  }
  else {return false;}
}
boolean RoverControl::isRemote(void){
  if(!mazeMode and remoteMode){
    return true;
  }
  else {return false;}
}
boolean RoverControl::isMaze(void){
  if(mazeMode and !remoteMode){
    return true;
  }
  else {return false;}
}
void RoverControl::interface(void){
  WiFiClient client = server.available();
  if(!mazeMode or !remoteMode){
    select(client);
  }
  else if(mazeMode and !remoteMode){
    mazeInterface(client);
  }
  else if(!mazeMode and remoteMode){
    remoteInterface(client);
  }
}
void RoverControl::select(WiFiClient client){
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
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
        }
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          //client.println("Connection: Keep-Alive");
          //client.println("Keep-Alive: timeout=5, max=1000");
          client.println("Content-type:text/html");
          client.println();
          client.println("<html>");
          client.println("<head>");
          client.println("<style>");
          client.println("a.button {-webkit-appearance: button;");
          client.println("-moz-appearance: button;");
          client.println("appearance: button;");
          client.println("height:200px;");
          client.println("line-height:200px;");
          client.println("text-align:center;");
          client.println("text-decoration: none;");
          client.println("font-size: 50px;");
          client.println("color: initial;}");
          client.println("</style>");
          client.println("<title>Rover Control Menu</title>");
          client.println("</head>");
          client.println("<body>");
          // Button for maze mode
          client.println("<a href=\"/?maze\" class=\"button\" style=\"width:100%;\"\">MAZE SOLVER</a>");
          client.println("<br />");
          client.println("<a href=\"/?remote\" class=\"button\" style=\"width:100%;\"\">REMOTE CONTROL</a>");
          client.println("</body>");
          client.println("</html>");
          client.println();
          break;
        }
        // Decide which button was clicked (if any)
        // Maze Mode button
        if (readString.indexOf("?maze") > 0){
          mazeMode = true;
          remoteMode = false;
          readString = ""
          mazeInterface(client);
        }
        // Remote Mode button
        if (readString.indexOf("?remote") > 0){
          mazeMode = false;
          remoteMode = true;
          readString = ""
          remoteInterface(client);
        }
      }
    }
    delay(1);
    client.stop();
    if(Serial){
      Serial.println("client disconnected");
      Serial.println();
    }
  }
}

void RoverControl::mazeInterface(WiFiClient client){
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
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
        }
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Connection: Keep-Alive");
          client.println("Keep-Alive: timeout=5, max=1000");
          client.println("Content-type:text/html");
          client.println();
          client.println("<html>");
          client.println("<head>");
          client.println("<style>");
          client.println("a.button {-webkit-appearance: button;");
          client.println("-moz-appearance: button;");
          client.println("appearance: button;");
          client.println("height:200px;");
          client.println("line-height:200px;");
          client.println("text-align:center;");
          client.println("text-decoration: none;");
          client.println("font-size: 50px;");
          client.println("color: initial;}");
          client.println("</style>");
          client.println("<title>Rover Maze</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("Hello World");
          // Button for maze mode
          // client.println("<a href=\"/?maze\" class=\"button\" style=\"width:100%;\"\">MAZE SOLVER</a>");
          // client.println("<br />");
          // client.println("<a href=\"/?remote\" class=\"button\" style=\"width:100%;\"\">REMOTE CONTROL</a>");
          client.println("</body>");
          client.println("</html>");
          client.println();
          break;
        }
        // Decide which button was clicked (if any)
        // Maze Mode button
        if (readString.indexOf("?fast") > 0){
          mazeMode = true;
          remoteMode = false;
          // Clear the readString to be able to get the next command
          readString = "";
        }
        // Remote Mode button
        if (readString.indexOf("?slow") > 0){
          mazeMode = false;
          remoteMode = true;
          // Clear the readString to be able to get the next command
          readString = "";
        }
      }
    }
    delay(1);
    client.stop();
    if(Serial){
      Serial.println("client disconnected");
      Serial.println();
    }
  }
}

void RoverControl::remoteInterface(WiFiClient client){
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
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
        }
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Connection: Keep-Alive");
          client.println("Keep-Alive: timeout=5, max=1000");
          client.println("Content-type:text/html");
          client.println();
          client.println("<html>");
          client.println("<head>");
          client.println("<style>");
          client.println("a.button {-webkit-appearance: button;");
          client.println("-moz-appearance: button;");
          client.println("appearance: button;");
          client.println("height:200px;");
          client.println("line-height:200px;");
          client.println("text-align:center;");
          client.println("text-decoration: none;");
          client.println("font-size: 50px;");
          client.println("color: initial;}");
          client.println("</style>");
          client.println("<title>Rover Control Interface</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("Hello remote");
          // Button for maze mode
          // client.println("<a href=\"/?maze\" class=\"button\" style=\"width:100%;\"\">MAZE SOLVER</a>");
          // client.println("<br />");
          // client.println("<a href=\"/?remote\" class=\"button\" style=\"width:100%;\"\">REMOTE CONTROL</a>");
          client.println("</body>");
          client.println("</html>");
          client.println();
          break;
        }
        // Decide which button was clicked (if any)
        // Maze Mode button
        if (readString.indexOf("?fast") > 0){
          mazeMode = true;
          remoteMode = false;
          // Clear the readString to be able to get the next command
          readString = "";
        }
        // Remote Mode button
        if (readString.indexOf("?slow") > 0){
          mazeMode = false;
          remoteMode = true;
          // Clear the readString to be able to get the next command
          readString = "";
        }
      }
    }
    delay(1);
    client.stop();
    if(Serial){
      Serial.println("client disconnected");
      Serial.println();
    }
  }
}
