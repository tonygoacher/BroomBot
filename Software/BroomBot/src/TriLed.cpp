
#include "TriLed.h"


TriLed* TriLed::Instance()
{
    static TriLed* instance = new TriLed();
    return instance;
}
void TriLed::Init(int redLedPort, int greenLedPort)
{
      redPort = redLedPort;
      greenPort = greenLedPort;
      patternDelay = 100;
      currentTimer = millis() + patternDelay;
      redPattern = 0L;
      greenPattern = 0L;
      digitalWrite(redPort,LOW);
      digitalWrite(greenPort,LOW);
      pinMode(redPort,OUTPUT);
      pinMode(greenPort,OUTPUT); 
      Serial.begin(9600);
}

void TriLed::SetRed(uint64_t newRedPattern)
{
    redPattern = newRedPattern;
}

void TriLed::SetGreen(uint64_t newGreenPattern)
{
    greenPattern = newGreenPattern;  
}

void TriLed::SetPatternDelay(int delay)
{
    patternDelay = delay;
    currentTimer = millis() + patternDelay;   
}

void TriLed::Run()
{

    if(millis() >= currentTimer)   
    {
      
        currentTimer = millis() + patternDelay;
        mask >>=1;
        if(mask == 0)
        {
            mask = maskReset;
        }
        SetLed(redPort, redPattern);
        SetLed(greenPort, greenPattern);
    }
}

void TriLed::SetLed(int port , uint64_t portMask)
{
    digitalWrite(port, (portMask & mask) != 0);
}

