#include "MainStateMachine.h"
#include "InitBroomBot.h"




// Import the created staes from main.cpp here
extern InitBroomBot initBroomBotState;


MainStateMachine::MainStateMachine(IState* stateMachine[], int numberOfStates)
{
 
    statesOfTheMachine = stateMachine;

    numStates = numberOfStates;
    currentState = initialState;

    
    
}

void MainStateMachine::StartStateMachine()
{
    statesOfTheMachine[currentState]->Entry();
}

void MainStateMachine::Run()
{
    int nextState = statesOfTheMachine[currentState]->Run();

    if(nextState != noStateChange)
    {

        if(nextState < numStates)
        {
            currentState = nextState;

            statesOfTheMachine[currentState]->Entry();
     
        }
        else
        {
            Serial.print("Error state ");
            Serial.print(nextState);
            Serial.print(" exceeds states machine size of ");
            Serial.println(numStates);
        }
    }
}

