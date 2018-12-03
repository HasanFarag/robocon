#ifndef WIRELESS_H
#define WIRELESS_H

#include <SPI.h>
#include <WiFi101.h>

class Wireless{
public:
  Wireless();
  boolean isConnected(void);
  boolean hasCredentials(void);
  void accessPoint(void);
  void wifiCredentials(void);
  void connectWifi(void);
  void printWiFiStatus(void);
  void printAPStatus(void);
private:
  char* const apssid="MKR1000AP";
  int status;
  String HTTP_req;
  String password;
  String network;
  boolean readingNetwork;
  boolean readingPassword;
  boolean WiFiConnected;
};

class RoverControl{
public:
  RoverControl();
  //void select(void);
  void interface(void);
private:
  boolean mazeMode;
  boolean remoteMode;
  boolean readingCommand;
  String readString;
  boolean isNone(void);
  boolean isRemote(void);
  boolean isMaze(void);
  void select(WiFiClient client);
  void mazeInterface(WiFiClient client);
  void remoteInterface(WiFiClient client);
};
#endif
