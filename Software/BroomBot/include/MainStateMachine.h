#ifndef __MAINSTATEMACHINE_H__
#define __MAINSTATEMACHINE_H__

#include <Arduino.h>
#include "IState.h"



// Initial state must always be zero

class MainStateMachine
{
public:
    MainStateMachine(IState* states[], int numStates);
    void StartStateMachine();
    void Run();

    static const int noStateChange = 9999;
private:
    static const int initialState = 0;

    IState** statesOfTheMachine;
    int currentState;
    int numStates;
};

#endif // __MAINSTATEMACHINE_H__