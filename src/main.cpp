/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Ben B & Felix H                                           */
/*    Created:      9/15/2026, 4:18:50 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "utils/helperMethods.h"
#include <string>
#include <cmath>
#include <algorithm>

using namespace vex;
using namespace std;

competition Competition;

brain Brain;
controller Controller = controller(primary);
motor leftMotor = motor(PORT6);
motor rightMotor = motor(PORT5);
motor clawRaiser = motor(PORT1);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);

  resetAllMotors(); 
  setSpeed(100);

  printLineToScreen("hello world");
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
    if (Controller.ButtonL1.pressing()){
      raiseClaw();
    }

    if (Controller.ButtonL2.pressing()){
      lowerClaw();
    }

    while (true) {
        drawScreen();

        leftSide(-600 * (Controller.Axis2.position()/100)); 
        rightSide(600 * (Controller.Axis3.position()/100)); 

        wait(20, msec);
    }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();
  
  while (true) {
    
    wait(100, msec);
  }
}