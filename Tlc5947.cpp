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


#include "Tlc5947.h"

#define TLC5947_CS_PIN 8 

Tlc5947::Tlc5947() {

  //Set the chip select pin to output and pull it high (disable)
  pinMode(TLC5947_CS_PIN, OUTPUT);
  digitalWrite(TLC5947_CS_PIN, HIGH);
  
  //Start SPI
  SPI.begin();
}
    
void Tlc5947::refresh() {

    //Pull chip select low
    digitalWrite(TLC5947_CS_PIN, LOW);

    for (byte _led=0; _led<NUM_LEDS; _led+=2) { //skip every other channel because we pack 2 LEDs of data into 3 bytes
      word _even; //even numbered LED GS value (starting at zero) 
      word _odd; //odd numbered LED GS value (starting at one)
      
      byte _byte1;
      byte _byte2;
      byte _byte3;
      
      _even=this->gsdata[_led]*GS_SCALE_FACTOR;

      if (_led+1 == NUM_LEDS) {
        _odd=0; //if the number of LEDs is odd (final _led is even), set up a fake final LED value of 0
      }
      
      else { 
        _odd=this->gsdata[_led+1]*GS_SCALE_FACTOR; //scale the odd value
      }
      
      // Generate the three bytes from data for 2 LEDS to send to the chip
      _byte1 = (byte)((_even >> 4) & 0xFF); //first byte is the first 8 bits of even numbered LED
      _byte2 = (byte)((_even << 4) & 0xF0) | (byte)((_odd >> 8) & 0x0F); //second byte is the last 4 bits of even and first 4 bits of odd numbered LED  
      _byte3 = (byte)(_odd & 0xFF); //third byte is last 8 bits of odd numbered led
      
      // Send the bytes
      SPI.transfer(_byte1);
      SPI.transfer(_byte2);
      SPI.transfer(_byte3);
    }
 
    //Pull chip select high
    digitalWrite(TLC5947_CS_PIN, HIGH);
    
}

