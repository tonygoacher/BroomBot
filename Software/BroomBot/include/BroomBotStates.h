#ifndef __BROOMBOTSTATES_H__
#define __BROOMBOTSTATES_H__

#include "MainStateMachine.h"

class BroomBotStates
{
public:
    enum States
    {
        INIT_BOT,
        IDLE,
        SMALL_RISE_AND_HOVER,
        FAST_RESET,
        MED_RISE_AND_HOVER,
        FULL_RISE,

        NUM_STATES,
        NO_STATE = 9999,  // This is the state ID if there is no state change.
    };
};
#endif // __BROOMBOTSTATES_H__