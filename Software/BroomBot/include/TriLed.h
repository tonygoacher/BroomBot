#ifndef __TRILED_H__
#define __TRILED_H__
#include <Arduino.h>


class TriLed
{
public:

    void Init(int redLedPort, int greenLedPort);
    void SetRed(uint64_t redPattern);
    void SetGreen(uint64_t greenPattern);
    void SetPatternDelay(int delay);
    void Run();
    static TriLed* Instance();
private:
    TriLed(){};
    void SetLed(int port , uint64_t portMask);
  
    uint64_t redPattern;
    uint64_t greenPattern;
    unsigned long currentTimer;
    int patternDelay;    
    int redPort;
    int greenPort;
    uint64_t mask;
    static const uint64_t maskReset = 0x80000000L;


};
#endif // __TRILED_H__