/* rover api*/
#ifndef ROVER_H
#define ROVER_H

class Rover{
public:
  Rover();
  //Main drive methods
  void driveForwards(uint8_t speed, uint8_t distance);
  void driveReverse(uintt8_t speed, uint8_t distance);
  void driveLeft(uint8_t speed, uint16_t angle);
  void driveRight(uint8_t speed, uint16_t angle);
  void driveStop(void);
  void driveMotorsSpeed(uint8_t left, uint8_t right);
  //Cannon methods
  void cannonUp(void);
  void cannonDown(void);
  void cannonFire(void);
  //Sensor methods
  float readUltrasonic(uint8_t sensor);
  void readUltrasonicArray(float* sensorArrayptr);
  float readLIDAR(void);
  float mainBatteryVoltage(void);
  /*We might do some calculations. These helper
    functions set up various parameters*/
  wheelDiameter(uint8_t millimeters);
private:
  uint8_t _wheelDiameter;
  float
};
