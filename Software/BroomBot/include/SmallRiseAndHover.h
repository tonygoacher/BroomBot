#ifndef __SMALLRISEANDHOVER_H__
#define __SMALLRISEANDHOVER_H__

#include "IState.h"

class RTStepper;
class IRemote;
class SmallRiseAndHover : public IState
{
public:
    SmallRiseAndHover(IRemote* theButton, RTStepper* stepper, int theHoverHigh, int theHoverDelta);
    void Entry() override;
    int Run() override;
private:
    enum  SmallRiseWithHoverState
    {
        InitialRise,
        HoverDown,
        HoverUp,
    };

    SmallRiseWithHoverState state;
    RTStepper* stepper;
    IRemote* button;

    int hoverHigh = 400;
    int hoverDelta = 200;

};

#endif // __SMALLRISEANDHOVER_H__