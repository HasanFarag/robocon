#include "Wireless.h"
#include <RTCZero.h>



Wireless wireless;
RoverControl control;

void setup() {
  Serial.begin(9600);
  if(!Serial) {
    delay(10000); // wait for serial port to connect. Needed for native USB port only
  }

  //start wireless access server
  wireless.accessPoint();
  //intialise main motors
  //initialise cannon motors
  //initalise ultrasonic sensor array
  //initialise lidar
  //start real time clock
   

}

void loop() {
  // put your main code here, to run repeatedly:

  if(!wireless.hasCredentials()){
    //initialise WiFi
    wireless.wifiCredentials();
  }
  else if(!wireless.isConnected()){
    //stop wireless access server
    //start webserver
    wireless.connectWifi();
    //update real time clock
  }

  if(wireless.isConnected()){
    control.interface();
  }


}
