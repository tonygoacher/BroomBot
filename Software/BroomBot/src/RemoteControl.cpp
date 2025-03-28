#include "RemoteControl.h"

RemoteControl::RemoteControl(uint8_t vtPort, uint8_t switchPorts[])
{
    vt = vtPort;
    pinMode(vt, INPUT);

    for(int i = 0 ; i < RemoteControl::MaxPorts ; i++)
    {
        ports[i] = switchPorts[i];
        pinMode(ports[i], INPUT);
    }

    if(digitalRead(vt) == HIGH)
    {
        currentState = RemoteState::AWAITING_SIGNAL_DROP;   
    }
    else
    {
        currentState = RemoteState::SEEKING_SIGNAL;
    }

    nextPollTime = millis() + 50;
}

IRemote::Button RemoteControl::ReadButton()
{
    static const IRemote::Button buttonID[] = {IRemote::Button::A, Button::B, Button::C, Button::D};
    for(uint8_t i = 0 ; i < RemoteControl::MaxPorts ; i++)
    {
        if(digitalRead(ports[i]))
        {
            Serial.print("Got button ");
            Serial.println(buttonID[i]);
            return buttonID[i];
        }
    }
    return IRemote::Button::NOTHING;
}

IRemote::Button RemoteControl::GetRemote()
{
    if(millis() >= nextPollTime)
    {
        nextPollTime = millis() + 50;

        switch(currentState)  
        {
            case RemoteControl::SEEKING_SIGNAL:
            {
                if(digitalRead(vt) == HIGH)
                {
                    currentState = RemoteControl::AWAITING_SIGNAL_DROP;
                    return ReadButton();
                }
            }
            break;

            case RemoteControl::AWAITING_SIGNAL_DROP:
            {
                if(digitalRead(vt) == LOW)
                {
                    currentState = RemoteControl::SEEKING_SIGNAL;
                }
            }
        }
    }
    return IRemote::Button::NOTHING;
}

