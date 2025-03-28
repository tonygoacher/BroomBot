#include <Arduino.h>
#include "RTStepper.h"
#include "FastReset.h"
#include "Ports.h"
#include "BroomBotStates.h"

FastReset::FastReset(RTStepper* theStepper)
{
    stepper = theStepper;    
}

void FastReset::Entry()
{   
    if(digitalRead(LIMIT_SWITCH) == LOW)
    {
        state = QUIT;
    }
    else
    {
        stepper->SetAcceleration(3000);
        stepper->SetMaxSpeed(4000);
        stepper->MoveTo(-600);
        state = DO_RESET;
    }
}

void FastReset::SetZero()
{
    stepper->SetCurrentPos(0);
    stepper->MoveTo(0);
}


int FastReset::Run()
{
    BroomBotStates::States nextState = BroomBotStates::NO_STATE;
    if(state == QUIT)
    {
        SetZero();
        nextState =  BroomBotStates::IDLE;
    }

    if(state == DO_RESET)
    {
        if(!stepper->Running() || digitalRead(LIMIT_SWITCH) == LOW)
        {
            SetZero();
            nextState =  BroomBotStates::IDLE;
        }
    }
    return nextState; 
}

