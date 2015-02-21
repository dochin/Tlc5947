/*
TLC5947 24 channel 12-bit PWM LED driver

Purpose: Driver for TLC5947

Copyright 2015 Jason Campbell, dochin@campound.org
Licensed under GPL v2 or later

Changelog:
2/21/15 Untested based on datasheet

Notes: 

Be sure to define the chip select pin and number of LEDs in .h file

USAGE:
======
Tlc5947 myLedDriver; //Initialize object
myLedDriver.gsdata[0]=255; //Write 255 grayscale setting to LED number 0
myLedDriver.refresh(); //Send data stored in gsdata to the LED driver

*/

#ifndef Tlc5947_h
  #define Tlc5947_h
#endif

#include "Arduino.h"
#include "SPI.h"

#define NUM_LEDS 16
#define TLC5947_CS_PIN 8 

class Tlc5947 {
  public:
    Tlc5947();
 
    //function to write data to LEDs
    void refresh();

    //grayscale data
    byte gsdata[NUM_LEDS];

  private:
    byte _channel;

};

