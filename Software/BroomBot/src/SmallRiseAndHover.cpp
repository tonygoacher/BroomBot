#include "SmallRiseAndHover.h"
#include "RTStepper.h"
#include "BroomBotStates.h"
#include "IRemote.h"

SmallRiseAndHover::SmallRiseAndHover(IRemote* theButton, RTStepper* theStepper,int theHoverHigh, int theHoverDelta)
{
    stepper = theStepper;
    button = theButton;
    hoverHigh = theHoverHigh;
    hoverDelta = theHoverDelta;
}

void SmallRiseAndHover::Entry()
{
    state = InitialRise;
	stepper->SetAcceleration(2000.0);
    stepper->SetMaxSpeed(2000.0f);
    Serial.println("SMallRiseAndHover::Entry");
    stepper->MoveTo(hoverHigh);

}

int SmallRiseAndHover::Run()
{
    switch(state)
    {
        case InitialRise:
        {
            if(!stepper->Running())
            {
                stepper->MoveTo(stepper->GetPos() - hoverDelta);
                stepper->SetMaxSpeed(500.0f);
                stepper->SetAcceleration(500.0);
                state = HoverDown;
            }
        }
        break;

        case HoverDown:
        {
            if(!stepper->Running())
            {
                stepper->MoveTo(stepper->GetPos() + hoverDelta);
                state = InitialRise;
            }
        }
        break;
    }
    if(button->GetRemote() == IRemote::D)
    {
        return BroomBotStates::FAST_RESET;
    }

    return BroomBotStates::NO_STATE;
    
}
