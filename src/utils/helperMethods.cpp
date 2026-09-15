#include "vex.h"
#include <string>

using namespace vex;
using namespace std;

extern vex::brain Brain;
extern vex::controller Controller;
extern vex::motor motor1;

int SPEED = 10;
int MAX_SPEED = 600;

void printToScreen(string message) {
    Brain.Screen.print("%s", message.c_str());
}

void printLineToScreen(string message){
    Brain.Screen.print("%s", message.c_str());
    Brain.Screen.newLine();
}

void clearScreen(){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
}

bool motor1Active = false;

void toggleMotor1(){
    motor1Active = !motor1Active;
    if (motor1Active == true) {
        motor1.setVelocity(SPEED, vex::pct);
        motor1.spin(vex::forward);
    } else {
        motor1.stop();
    }
}

void resetAllMotors(){
    motor1.setPosition(0, vex::deg);
}

void setSpeed(int speed){
    SPEED = speed;
    clearScreen();

    if (SPEED > MAX_SPEED){
        SPEED = MAX_SPEED;
    }

    Brain.Screen.print("%d", SPEED);
    if (SPEED == MAX_SPEED){
        Brain.Screen.print(" (Max)");
    }
}

int getSpeed(){
    return SPEED;
}

void drawScreen(){
    Controller.Screen.clearScreen();
    clearScreen();
    Brain.Screen.drawCircle(50, 50, 50);
}