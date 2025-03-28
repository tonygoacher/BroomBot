

#include "Idle.h"
#include "IRemote.h"
#include "BroomBotStates.h"
#include "TriLed.h"



Idle::Idle(IRemote* theRemote)
{
    remote = theRemote;
 
}

void Idle::Entry()
{
    
    Serial.println("Idle::Entry");
    TriLed::Instance()->SetRed(0);
    TriLed::Instance()->SetGreen(0xFF00FF00);  

}

int Idle::Run()
{
  
    BroomBotStates::States nextState = BroomBotStates::States::NO_STATE;

    IRemote::Button button = remote->GetRemote();
    Serial.println(button);
    switch(button)
    {
        case   IRemote::Button::A:
        {
            Serial.println("Got button A");
            nextState = BroomBotStates::SMALL_RISE_AND_HOVER;
        }
        break;

        case   IRemote::Button::B:
        {
            Serial.println("Got button B");
            nextState = BroomBotStates::MED_RISE_AND_HOVER;
        }
        break;

        case   IRemote::Button::C:
        {
            Serial.println("Got button C");
            nextState = BroomBotStates::FULL_RISE;
        }
        break;

        case   IRemote::Button::D:
        {
            Serial.println("Got button D");
                // Reset to idle
        }
        break;

        default:;
    }

    return nextState;
}
