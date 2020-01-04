/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/
#ifndef UNIT_TEST
#include <ESP8266WiFi.h>
#else
#include "MockArduino.h"
#endif


#define CLOCK_DELAY_MS 10
//#define MULTI_CLOCK 1

#define TICK_CLOCK(PIN) digitalWrite(PIN, LOW); delay(CLOCK_DELAY_MS); digitalWrite(PIN, HIGH); delay(CLOCK_DELAY_MS);
#define CHANNEL_COUNT 3
#ifdef MUTLI_CLOCK
static int  _serialCounts[CHANNEL_COUNT];
static uint8_t _clocks[CHANNEL_COUNT];
#else
static uint8_t _clock;
static int _serialCount;
#endif

static uint8_t _dataOutPins[CHANNEL_COUNT];

#ifdef MULTI_CLOCK
void writeStartFrame(int * data, int channel)
#else
void writeStartFrame(int * data[])
#endif
{
  //start frame
  #ifndef MULTI_CLOCK
  for (int channel = 0; channel < CHANNEL_COUNT; ++channel)
  #endif
    digitalWrite(_dataOutPins[channel], 0);
  
  for (int mask = 0; mask < 32; ++mask)
  {
    #ifdef MULTI_CLOCK
      TICK_CLOCK(_clocks[channel});
    #else
      TICK_CLOCK(_clock);
    #endif
  }
}


#ifdef MULTI_CLOCK
void writeEndFrame(int * data, int channel)
#else
void writeEndFrame(int * data[])
#endif
{
  //end frame  
  #ifndef MULTI_CLOCK
  for (int channel = 0; channel < CHANNEL_COUNT; ++channel)
  #endif
    digitalWrite(_dataOutPins[channel], 1);
  
  for (int mask = 0; mask < 32; ++mask)
  {
    #ifdef MULTI_CLOCK
      TICK_CLOCK(_clocks[channel});
    #else
      TICK_CLOCK(_clock);
    #endif
  }
}

//// Initializes the hardware for a shared clock system
//// Parameters:
//// dataOuts: the GPIO pin numbers for each individual channel
//// dataOutCount: How many GPIO pins
//// serialCount: How many Leds are in a row for each GPIO pin
//// clock: The gpio pin that is the clock
////
#ifdef MULTI_CLOCK
void led5050_init(int dataOuts[], int serialCounts[], int clocks[])
#else
void led5050_init(int dataOuts[], int serialCount, int clock)
#endif
{
  
  for (int channel = 0; channel < CHANNEL_COUNT; ++channel)
  {
    _dataOutPins[channel] = dataOuts[channel];
    #ifdef MULTI_CLOCK
    _serialCounts[channel] = serialCounts[channel];
    _clocks[channel] = clocks[channel];
    #endif
  }
  
  #ifndef MULTI_CLOCK
  _serialCount = serialCount;
  _clock = clock;
  #endif
  
  for(int channel = 0; channel < CHANNEL_COUNT; ++channel)
  {
    pinMode(dataOuts[channel], OUTPUT);
    digitalWrite(dataOuts[channel], LOW);
  }

  #ifdef MULTI_CLOCK
  for (int channel = 0; channel< CHANNEL_COUNT; ++channel)
  {
    int clock = _clocks[channel];
  #endif
    pinMode(clock, OUTPUT); 
    //Active LOW
    digitalWrite(clock, HIGH);
  
  #ifdef MULTI_CLOCK
  }
  #endif
    
}

#ifdef MULTI_CLOCK
void led5050_writeData(int data[], int channel){
  writeStartFrame(data,channel); 
  int ledCount = _serialCounts[channel];
#else
void led5050_writeData(int * data[]) {
  writeStartFrame(data);
  int ledCount = _serialCount;
#endif
  
  //Digits
  for (int i = ledCount; i >= 0; --i)
  {
    //Write the 3 bits
    #ifndef MULTI_CLOCK
    for (int channel = 0; channel < CHANNEL_COUNT; ++channel)
    #endif
        digitalWrite(_dataOutPins[channel], HIGH);  
    
    for (int mask = 0; mask < 3; ++mask)
    {
      #ifdef MULTI_CLOCK
        TICK_CLOCK(_clocks[channel});
      #else
        TICK_CLOCK(_clock);
      #endif
    }
    
    #ifdef MULTI_CLOCK
    int value = data[i];
    #endif
    
    //Write the brightness/colors
    for (int mask = 1 << 28; mask >=1; mask = mask >> 1)
    {
      
      #ifndef MULTI_CLOCK
      for (int channel = 0; channel < CHANNEL_COUNT; ++channel) {
        int value = data[channel][i];
      #endif
      
        digitalWrite(_dataOutPins[channel], (value & mask) ? HIGH : LOW);
      
      #ifdef MULTI_CLOCK
          TICK_CLOCK(_clocks[channel});
      #else
        }
        TICK_CLOCK(_clock);
      #endif
    }
  }

  #ifdef MULTI_CLOCK
    writeEndFrame(data, channel);
  #else
    writeEndFrame(data);
  #endif
}
