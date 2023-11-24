#pragma once
#include "vex.h"
#include "Control_Motors.h"

extern Control_Motors MyPaw;
extern Control_Motors MyVehicle;
extern Control_Motors InTakeRoll;
extern Control_Motors OutPutRoll;

void GyroTest(void);
void AutoSetup(void);
void PIDGyro(int HeadDegree);
void GoPidDegree(int head,int degree,int stopflag);
void ShootBallOnce(bool stopFlag,int ShootValue,int Sensorval);
int CheckBall(int checkvalue);
void RunPaw(int speed);
void AutoProRight(int LineTrackerValue);
void AutoProLeft(int LineTrackerValue);
void TurnWithRotation(int MyRotation,int leftspeed,int rightspeed);
void ShootBallOnce_B(int stopflag,int Sensorval);
void RollInBall(int SensorVal,int PawRunState);
void ShootCheckRPM(int MyRPM);