#ifndef __REMOTECONTROL_H__
#define __REMOTECONTROL_H__
#include <Arduino.h>
#include "IRemote.h"


class RemoteControl : public IRemote
{
public:
    RemoteControl(uint8_t vt, uint8_t switchPorts[]);

    IRemote::Button GetRemote() override;

private:
    IRemote::Button ReadButton();
    enum RemoteState
    {
        SEEKING_SIGNAL,
        AWAITING_SIGNAL_DROP,
    };

    RemoteState currentState;

    static const int MaxPorts = 4;
    uint8_t ports[MaxPorts];
    uint8_t vt;
    unsigned long nextPollTime;


};
#endif // __REMOTECONTROL_H__