#ifndef __FASTRESET_H__
#define __FASTRESET_H__

#include "IState.h"

class RTStepper;

class FastReset : public IState
{
public:
    FastReset(RTStepper* theStepper);

    int Run() override;
    void Entry() override;

private:
    void SetZero();
    enum FastResetStates
    {
        DO_RESET,
        QUIT,
    };

    FastResetStates state;

    RTStepper* stepper;    
};
#endif // __FASTRESET_H__