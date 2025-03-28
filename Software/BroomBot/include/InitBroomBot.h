#ifndef __InitBroomBot_H__
#define __InitBroomBot_H__

#include <Arduino.h>
#include "IState.h"

class RTStepper;
class TriLed;
class InitBroomBot : public IState 
{
public:
    InitBroomBot(RTStepper* stepper, uint8_t limitSwitch);
    void Entry() override;
    int Run() override;
private: 
    RTStepper* stepper;
    uint8_t limitSwitch;    

    enum InitBroomBots
    {
        SEEKING_NO_SWITCH,
        SEEKING_SWITCH,
        AWAIT_STOP,
    };

    InitBroomBots state;

    static const long seekNoSwitch = 100000;    // Positive is up
    static const long seekSwitch = -100000;


};
#endif // __InitBroomBot_H__