/*
TLC5947 24 channel 12-bit PWM LED driver

Purpose: Example program for TLC5947

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

#include "SPI.h" //This driver depends on the SPI library for hardware fast SPI
#include "Tlc5947.h"

Tlc5947 myLedDriver; //Constructor for the adc driver

void setup() {
  
}

void loop() {
  
    for (byte i=0; i < NUM_LEDS; i++) {
      myLedDriver.gsdata[i]=random(0,255); //assign a random grayscale value to each LED
    }
    
    myLedDriver.refresh();
    
    delay(500); 
 
}

