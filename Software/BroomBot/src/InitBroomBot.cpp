#include <Arduino.h>
#include "Ports.h"
#include "InitBroomBot.h"
#include "RTStepper.h"
#include "BroomBotStates.h"
#include "Direction.h"

InitBroomBot::InitBroomBot(RTStepper* theStepper, uint8_t limitSwitchPort)
{
    stepper = theStepper;
    limitSwitch = limitSwitchPort;
    pinMode(limitSwitch, INPUT_PULLUP);
}

void InitBroomBot::Entry()
{
    stepper->SetCurrentPos(0);
    if(digitalRead(limitSwitch) == HIGH)
    {
        // Limit switch is not seen, move down
        state = InitBroomBots::SEEKING_SWITCH;
    

        stepper->GotoRelative(seekSwitch);

        Serial.println("Start state is SEEKING_SWITCH");
    }
    else
    {
        state = InitBroomBots::SEEKING_NO_SWITCH;
        Serial.println("Start state is SEEKING_NO_SWITCH");
        stepper->GotoRelative(seekNoSwitch);
    }
}

int InitBroomBot::Run()
{
    BroomBotStates::States nextState = BroomBotStates::States::NO_STATE;
    switch(state)
    {
        case InitBroomBot::SEEKING_NO_SWITCH:
        {
            if(digitalRead(limitSwitch) == HIGH)
            {
                state = InitBroomBots::SEEKING_SWITCH;
                Serial.println("State is SEEKING_SWITCH");
                stepper->SetDirectionPin(DOWN);
                stepper->GotoRelative(seekSwitch);
            }
        }
        break;

        case InitBroomBot::SEEKING_SWITCH:
        {
            if(digitalRead(limitSwitch) == LOW)
            {
                stepper->Stop();
                stepper->SetCurrentPos(0);
                stepper->MoveTo(0);
   
                state = InitBroomBot::AWAIT_STOP;

                Serial.println("State is AWAIT_STOP");
            }
        }
        break;

        case InitBroomBot::AWAIT_STOP:
        {
            if(!stepper->Running())
            {
                nextState = BroomBotStates::States::IDLE;
            }
        }
    }
    return nextState;
}
