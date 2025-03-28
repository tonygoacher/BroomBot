#ifndef __IDLE_H__
#define __IDLE_H__

#include "IState.h"

class IRemote;
class TriLed;
class Idle : public IState
{
public:
    Idle(IRemote* theRemote);

    void Entry() override;
    int Run() override;

private:
    IRemote* remote;
    TriLed* led;

};
#endif // __IDLE_H__