
//// Initializes the hardware for a shared clock system
//// Parameters:
//// dataOuts: the GPIO pin numbers for each individual channel
//// dataOutCount: How many GPIO pins
//// serialCount: How many Leds are in a row for each GPIO pin
//// clock: The gpio pin that is the clock
////
void 5050_initSharedClock(int dataOuts[], int channelCount, int serialLedCount, int clock);
//// Writes data to the serial channels. Dimentionality MUST be the same as the configuration passed to dataOutCount/serialCount.
//// Value in array can be null when using mutli clock to indicate no change
//// arrayformat: [[<channel0led0ColorFrame>, <led1ColorFrame>,...] ,<Channel1Array>,...]
//// colorFrame: 32 bits xxxgggggrrrrrrrrggggggggbbbbbbbb
////            where x = 3 bits Dont Care
////                  g = 5 bits global brightness
////                  r/g/b 8 bit color value
 
void 5050_writeData(int * data[]);
