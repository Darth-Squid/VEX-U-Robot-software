#include "vex.h"
#include <string>
#include <cmath>

using namespace vex;
using namespace std;

extern vex::brain Brain;
extern vex::controller Controller;
extern vex::motor leftMotor;
extern vex::motor rightMotor;
extern vex::motor clawRaiser;

int SPEED = 10;
int MAX_SPEED = 600;

int LEFT_SPEED = 600;
int RIGHT_SPEED = 600;

int CURRENT_ANGLE = 1;

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

bool leftMotorActive = false;

void setLeftMotorSpeed(int speedPercent) {

    LEFT_SPEED = speedPercent;

    if (speedPercent == 0) {
        leftMotor.stop();
        return;
    }

    leftMotor.setVelocity(
        std::abs(speedPercent) * SPEED / 100.0,
        vex::rpm
    );

    if (speedPercent > 0)
        leftMotor.spin(vex::forward);
    else
        leftMotor.spin(vex::reverse);
}

void setRightMotorSpeed(int speedPercent) {

    RIGHT_SPEED = speedPercent;

    if (speedPercent == 0) {
        rightMotor.stop();
        return;
    }

    rightMotor.setVelocity(
        std::abs(speedPercent) * SPEED / 100.0,
        vex::rpm
    );

    if (speedPercent > 0)
        rightMotor.spin(vex::forward);
    else
        rightMotor.spin(vex::reverse);
}

void resetAllMotors(){
    leftMotor.setPosition(0, vex::deg);
    rightMotor.setPosition(0, vex::deg);
}

void setSpeed(int speed){
    SPEED = speed;
}

int getSpeed(){
    return SPEED;
}

void drawScreen(){
    Controller.Screen.clearScreen();
    clearScreen();

    //Controller.Screen.print("■■■■■■■■■■■■■■■■■■■■■■■■■"); Controller.Screen.newLine();
    //Controller.Screen.print("▮                      ▮"); Controller.Screen.newLine();
    //Controller.Screen.print("▮ Speed: %d  Angle: %d ▮", SPEED, CURRENT_ANGLE, 0); Controller.Screen.newLine();
    //Controller.Screen.print("▮                      ▮ "); Controller.Screen.newLine();
    //Controller.Screen.print("▮                      ▮ "); Controller.Screen.newLine();
    //Controller.Screen.print("▮                      ▮ "); Controller.Screen.newLine();
    //Controller.Screen.print("■■■■■■■■■■■■■■■■■■■■■■■■■"); Controller.Screen.newLine();
}

int getJoystickAngle() {
    int x = Controller.Axis1.value();
    int y = Controller.Axis2.value();

    if (x == 0 && y == 0) {
        return -1;
    }

    int angle = std::round(
        std::atan2(x, y) * 180.0 / M_PI
    );

    if (angle <= 0) {
        angle += 360;
    }

    return angle;
}

int getCurrentAngle(){
    return CURRENT_ANGLE;
}

double previousLeft = 0;
double previousRight = 0;

void updateCurrentAngle() {
    double left = leftMotor.position(vex::deg);
    double right = rightMotor.position(vex::deg);

    double leftChange = left - previousLeft;
    double rightChange = right - previousRight;

    double wheelCircumference = M_PI * 10; //Replace with wheel diameter

    double leftDistance =
        (leftChange / 360.0) * wheelCircumference;

    double rightDistance =
        (rightChange / 360.0) * wheelCircumference;

    double angleRadians =
        (rightDistance - leftDistance) / 50; //Replace with the distanc from one wheel to another (Doesn't have to be accurate)

    CURRENT_ANGLE += angleRadians * 180.0 / M_PI;

    previousLeft = left;
    previousRight = right;
}

int CLAW_HEIGHT = 0;

void raiseClaw(){
    if (CLAW_HEIGHT > 50) return;
    CLAW_HEIGHT += 1;

    clawRaiser.spin(vex::forward);
}

void lowerClaw(){
    if (CLAW_HEIGHT == 0) return;
    CLAW_HEIGHT -= 1;

    clawRaiser.spin(vex::reverse);
}