#pragma once
#include "vex.h"

#ifndef MyAbs
#define MyAbs(x)  x < 0 ? -x : x
#endif

#ifndef Control_Motors_DEBUG
#define Control_Motors_DEBUG 0
#endif

class Control_Motors
{
public:
	//STRUCTURE--------------------------------------------------------
	Control_Motors(int *MotorList,int MotorNumbers);
	Control_Motors(int *MotorList,int MotorNumbers,vex::velocityUnits velocityUnits);

	Control_Motors(int *MotorList,int MotorNumbers,vex::controller::button *RunFwd,vex::controller::button *RunRev);
	Control_Motors(int *MotorList,int MotorNumbers,vex::controller::button *RunFwd,vex::controller::button *RunRev,vex::velocityUnits velocityUnits);

	Control_Motors(int *MotorList,int MotorNumbers,vex::controller *Joystic);
	Control_Motors(int *MotorList,int MotorNumbers,vex::velocityUnits velocityUnits,vex::controller *Joystic);

	~Control_Motors();

	//Function--------------------------------------------------------------------------
	void SetUp(int *list);

	void RunMotors(int Pwr);   //run motors with same pwr
	void RunMotors(int *Pwr);  //run motors with different pwr
  void RunMotors(int Pwr,vex::velocityUnits MyVelocity);
  void RunMotors(int *Pwr,vex::velocityUnits MyVelocity);
  void RunMotors(double Vol,vex::voltageUnits Myvoltage);//run motors with same voltage
  void RunMotors(double *Vol,vex::voltageUnits Myvoltage);//run motors with different pwr
	void RunMotorsRotation(double RotationValue, int PwrOfMotor);
	void StopMotors(void);

	void RemoteMotors(int Pwr);
	void RemoteMotors(int PwrFwd,int PwrRev);
	void RemoteMotors(int *PwrFwd,int *PwrRev);

	void SetStopMode(vex::brakeType BreakMode); //set motor stop mode
  
	
	void SetTimeOut(int TimeMsValue);//Sets the timeout for the motor. If the motor does not reach its' commanded position prior to the completion of the timeout, the motor will stop.

	void SetMotorsName(char *name);

  void SetMaxTorque(int percent);

	void SetMotorsRotation(int value);
	void SetMotorsRotation(int value,vex::rotationUnits RotationUnits);
	int* GetSensorValue(void);
  int GetRpm(int motorNumber);
  int GetSpeed(int motorNumber);

	//Encoder------------------------------------
	void SetMyEncoder(vex::encoder *Encoder);
	int GetEncoderValue_Deg(void);


	#if Control_Motors_DEBUG
		bool setupFlag = false;
		int Control_Motors_DEBUG_LINE = 1;
		int Control_Motors_DEBUG_LIST = 1;
		int MotorShowLine = 3;

		void ShowDebugData(int StartLine,int StartList);
		void ShowMotorValue(int value);
		
		void printMotorName(void);
		void printStopMode(void);
		void printRemoteMode(void);
	#endif

protected:	
	//variable---------------------------------------------------------------------------
	vex::motor *MyMotorList = NULL;
	vex::brakeType MyBreakMode = vex::brakeType::coast;  //0.coast 1.brake 2.hold
	vex::velocityUnits MyVelocityUnits = vex::velocityUnits::pct; //0.pct 1.rpm 2.dps 
	vex::rotationUnits MyRotationUnits = vex::rotationUnits::deg; //0.deg 1.rev 2.raw
	vex::timeUnits MyTimeUnits = vex::timeUnits::msec;   //0.sec 1.msec

	vex::controller *MyJoystic = NULL;
	vex::controller::button *RunFwd = NULL;
	vex::controller::button *RunRev = NULL;
	
	vex::encoder *MyEncoder = NULL; //
	
	char *MyMotorsName = NULL;
	
	int MyMotorNumbers = 0; 

	bool RemoteMode = true;

	int *Sensorvalue = NULL;
	int *lastvalue = NULL;
	//Function--------------------------------------------------------------------------
	void CreatMotors(int *MotorList);
	void SetStopMode(void); 

	void GetRotationValue(void);
};





/*
//exp:

#include "robot-config.h"      
#include "MyClass/ver2.0/Control_Motors.cpp"

vex::controller Controller = vex::controller();
vex::bumper Bumper = vex::bumper(Brain.ThreeWirePort.H);

int main() {
                //port,gear,head
    int mo[] = {2,1,1,  //port2
                 9,1,0};//port9
    
    Control_Motors mymotor = Control_Motors(mo,2,&Controller);
    mymotor.SetStopMode(vex::brakeType::brake);
    
    #if Control_Motors_DEBUG
        mymotor.ShowDebugData(1,1);
    #endif
    
    mymotor.RunMotors(-30);
    vex::task::sleep(500);
    mymotor.StopMotors();
    
    mymotor.RunMotorsRotation(500,-50);    

    while(!Bumper.pressing())
    {
        mymotor.RemoteMotors(100,-50);
    }  
}
*/