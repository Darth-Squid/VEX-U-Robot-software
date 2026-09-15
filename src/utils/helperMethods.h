#ifndef DRIVE_H
#define DRIVE_H

#include "vex.h"
#include <string>

void printToScreen(std::string message);
void printLineToScreen(std::string message);

void toggleMotor1();
void resetAllMotors();
void setSpeed(int speed);
int getSpeed();
void drawScreen();

#endif