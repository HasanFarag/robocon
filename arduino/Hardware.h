/*
  hardware.h - Library file for rover hardware
  Created by Bill Crawford <bill.crawford@forthvalley.ac.uk>
  Stepper motor requires 4 GPIO pins

  For the Utrasonic sensors we will connect to a MCP23017A Port
  Expander. This uses I2C to communicate with the Raspberry Pi.

  Laser rangefinder for target distance uses I2C or PWM input
  (could use an interrupt pin for this).

  Main drive motors each require 2 GPIO for forward reverse
  and 2 PWM speed signals also 2 or 1 GPIO for inhibits.
  Wheel Speed sensors 2 GPIO

  Possibly need a motor for cannon charge system. 1 GPIO or PWM

  GPIO Count

*/

#ifndef hardware_h
#define hardware_h


#endif
