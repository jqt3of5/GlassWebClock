/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/
#include <ESP8266WiFi.h>

#define CLOCK_DELAY_MS 10
//#define MULTI_CLOCK 1

#define TICK_CLOCK(PIN) digitalWrite(c, LOW); delay(CLOCK_DELAY_MS); digitalWrite(c, HIGH); delay(CLOCK_DELAY_MS);

#ifdef MUTLI_CLOCK
static int * _clocks;
static int * _serialCounts;
#else
static int _clock;
static int _serialCount;
#endif

static int * _dataOuts;
static int _dataOutCount;

void writeStartFrame(int * data[])
{
  //start frame
  for (int channel = 0; channel < _dataOutCount; ++channel)
  {
    
    #ifdef MULTI_CLOCK
      if (data[channel] == 0)
      {
        continue;
      }
    #endif
    digitalWrite(_dataOuts[channel], 0);
  }
  
  for (int mask = 0; mask < 32; ++mask)
  {
    #ifdef MULTI_CLOCK
      for(int channel = 0; channel < _dataOutCount; ++channel)
      {
        if (data[channel] == 0)
        {
          continue;
        }
        TICK_CLOCK(_clocks[channel});
      }
    #else
      TICK_CLOCK(_clock);
    #endif
  }
}
void writeEndFrame(int * data[]){
  //end frame  
  for (int i = 0; i < _dataOutCount; ++i)
  {
    #ifdef MULTI_CLOCK
        if (data[channel] == 0)
        {
          continue;
        }
    #endif
    digitalWrite(_dataOuts[i], 1);
  }

  for (int mask = 0; mask < 32; ++mask)
  {
    #ifdef MULTI_CLOCK
      for(int channel = 0; channel < _dataOutCount; ++channel)
      {
        if (data[channel] == 0)
        {
          continue;
        }
        TICK_CLOCK(_clocks[channel});
      }
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
void 5050_initSharedClock(int dataOuts[], int dataOutCount, int serialCount, int clock)
{
  _dataOuts = (int*)calloc(dataOutCount, sizeof(int));
  _dataOutCount = dataOutCount;
  _serialCount = serialCount;
  _clock = clock;
  
  for(int i = 0; i < dataOutCount; ++i)
  {
    pinMode(dataOuts[i], OUTPUT);
    digitalWrite(dataOuts[i], LOW);
  }
  
  pinMode(clock, OUTPUT); 

  //Active LOW
  digitalWrite(clock, HIGH);
}

//// Parameters:
//// dataOuts: the GPIO pin numbers for each individual channel
//// serialCounts: How many Leds are in a row for each GPIO pin
//// clocks: The gpio pin that is the clock
//// count: The numeber of individual channels
/** Not Implemented **
void 5050_initMultiClock(int dataOuts[], int serialCounts[], int clocks[], int count)
{
  
}
*/

void 5050_writeData(int * data[]) {
  
  writeStartFrame(data);
  //Digits
  for (int i = _serialCount; i >= 0; --i)
  {
    //Write the 3 bits
    for (int channel = 0; channel < _dataOutCount; ++channel)
    {
      #ifdef MULTI_CLOCK
        if (data[channel] == 0)
        {
          continue;
        }
      #endif
        digitalWrite(_dataOuts[channel], HIGH);  
    }
    for (int mask = 0; mask < 3; ++mask)
    {
      #ifdef MULTI_CLOCK
        for(int channel = 0; channel < _dataOutCount; ++channel)
        {
          if (data[channel] = 0)
          {
            continue;
          }
          TICK_CLOCK(_clocks[channel});
        }
      #else
        TICK_CLOCK(_clock);
      #endif
    }

    //Write the brightness/colors
    for (int mask = 28; mask >=0; --mask)
    {
      for (int channel = 0; channel < _dataOutCount; ++channel)
      {
        
        #ifdef MULTI_CLOCK
          if (data[channel] == 0)
          {
            continue;
          }
        #endif
        digitalWrite(_dataOuts[channel], (data[channel][i] & 1 << mask) ? HIGH : LOW);
      }
      
      #ifdef MULTI_CLOCK
        for(int channel = 0; channel < _dataOutCount; ++channel)
        {
          if (data[channel] = 0)
          {
            continue;
          }
          TICK_CLOCK(_clocks[channel});
        }
      #else
        TICK_CLOCK(_clock);
      #endif
    }
  }
  writeEndFrame(data);
 
}
