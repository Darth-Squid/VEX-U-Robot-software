#ifndef DRIVE_H
#define DRIVE_H

#include "vex.h"
#include <string>

void printToScreen(std::string message);
void printLineToScreen(std::string message);

void setLeftMotorSpeed(int speedPercentage);
void setRightMotorSpeed(int speedPercentage);

void resetAllMotors();
void setSpeed(int speed);
int getSpeed();
void drawScreen();

int getJoystickAngle();
int getCurrentAngle();
void updateCurrentAngle();

void raiseClaw();
void lowerClaw();
#endif