#ifdef UNIT_TEST
#define HIGH 1
#define LOW 0
#define OUTPUT 1

int pinStates[15] = {0};
int * pinHistories[15] = {0};
int pinHistoryCount[15] = {0};

void delay(int ms)
{
  
}
void pinMode(int pin, int mode){
  
}
void digitalWrite(int pin, int value)
{
  pinStates[pin] = value;

  if (pinHistories[pin] == 0)
  {
    pinHistories[pin] = (int*)calloc(sizeof(int), 1000);
  }
  
  int count = pinHistoryCount[pin];
  pinHistories[pin][count] = value;
  pinHistoryCount[pin] = count + 1;
}
#endif
