#include <Arduino.h>

#include "Ports.h"
#include "TriLed.h"
#include "RTStepper.h"
#include "RemoteControl.h"
#include "Ports.h"

#include "InitBroomBot.h"
#include "MainStateMachine.h"
#include "BroomBotStates.h"
#include "Idle.h"
#include "SmallRiseAndHover.h"
#include "FastReset.h"



RTStepper stepper(STEP_PULS, STEP_DIR, STEP_EN);

uint8_t remotePorts[] = {BUTTONA,BUTTONB,BUTTONC,BUTTOND};
RemoteControl remote(SIGNAL_VT, remotePorts);

InitBroomBot initBroomBotState(&stepper, LIMIT_SWITCH);
Idle idleState(&remote);
SmallRiseAndHover smallRiseAndHoverState(&remote, &stepper, 400 , 200);
SmallRiseAndHover mediumRiseAndHoverState(&remote, &stepper, 1600 , 200);
SmallRiseAndHover fullRise(&remote, &stepper, 2800 , 0);

FastReset fastReset(&stepper);

IState* broomBot[]=
{
  &initBroomBotState,
  &idleState,
  &smallRiseAndHoverState,
  &fastReset,
  &mediumRiseAndHoverState,
  &fullRise
};

MainStateMachine stateMachine(broomBot, BroomBotStates::NUM_STATES);



void setup()
{
  TriLed::Instance()->Init(RED_LED,GREEN_LED);

  Serial.begin(9600);
  TriLed::Instance()->SetRed(0x55555555);
  TriLed::Instance()->SetGreen(0xAAAAAAAA);
  TriLed::Instance()->SetPatternDelay(100);

  pinMode(STEP_DIR, OUTPUT);
  pinMode(STEP_EN, OUTPUT);
  pinMode(STEP_PULS, OUTPUT);
  digitalWrite(STEP_DIR,LOW);

  stateMachine.StartStateMachine();
  stepper.Enable(true);

}

void loop() 
{
  TriLed::Instance()->Run();
  stepper.Run();
/*
  IRemote::Button button = remote.GetRemote();
  if(button != IRemote::Button::NOTHING)
  {
    Serial.print("Got button ");
    Serial.println(button);
  }
    */

 // digitalWrite(STEP_DIR,HIGH);
  stateMachine.Run();
 // digitalWrite(STEP_PULS,HIGH);
  //delay(100);
 // digitalWrite(STEP_PULS,LOW);
  //delay(100);

}

