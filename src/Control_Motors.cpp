#include "Control_Motors.h"

//STRUCTURE########################################################################################################

//以下为电机基本设置/配置

//--no remote mode------------------------------------------------------------------------------------
Control_Motors::Control_Motors(int *MotorList,int MotorNumbers)
{
	MyMotorNumbers = MotorNumbers;
	RemoteMode = false;

	SetUp(MotorList);
}

Control_Motors::Control_Motors(int *MotorList,int MotorNumbers,vex::velocityUnits velocityUnits)
{
	MyMotorNumbers = MotorNumbers;
	MyVelocityUnits = velocityUnits;
	RemoteMode = false;

	SetUp(MotorList);
}

//--user define button remote mode ----------------------------------------------------------------------
Control_Motors::Control_Motors(int *MotorList,int MotorNumbers,vex::controller::button *RunFwd,vex::controller::button *RunRev)
{
	MyMotorNumbers = MotorNumbers;
	this->RunFwd =RunFwd;
	this->RunRev =RunRev;
	SetUp(MotorList);
}

Control_Motors::Control_Motors(int *MotorList,int MotorNumbers,vex::controller::button *RunFwd,vex::controller::button *RunRev,vex::velocityUnits velocityUnits)
{
	MyMotorNumbers = MotorNumbers;
	MyVelocityUnits = velocityUnits;
	this->RunFwd =RunFwd;
	this->RunRev =RunRev;

	SetUp(MotorList);
}

//--defualt button remote-------------------------------------------------------------------------------
Control_Motors::Control_Motors(int *MotorList,int MotorNumbers,vex::controller *Joystic)
{
	MyMotorNumbers = MotorNumbers;
	MyJoystic = Joystic;

	SetUp(MotorList);
}

Control_Motors::Control_Motors(int *MotorList,int MotorNumbers,vex::velocityUnits velocityUnits,vex::controller *Joystic)
{
	MyMotorNumbers = MotorNumbers;
	MyVelocityUnits = velocityUnits;
	MyJoystic = Joystic;

	SetUp(MotorList);
}

Control_Motors::~Control_Motors()
{

}

//以上为电机基本设置/配置

//FUNCTION######################################################################################################################
/*public*********************************************************************************************/
void Control_Motors::SetUp(int *list)
{
	//set motor name设置电机名称
  char motorname[] = {"MyMotors"};
	SetMotorsName(motorname);

	//creat motor list	设置电机列表
	CreatMotors(list);
	SetStopMode();

	//set control button if remote mode	设置操作阶段控制按钮
	if(RemoteMode && MyJoystic != NULL)
	{
		RunFwd = &(*MyJoystic).ButtonL1;
		RunRev = &(*MyJoystic).ButtonL2;
	}

	//reset rotation设置初始角度
	SetMotorsRotation(0);

	//creat encoder value Array ，start value -1	设置编码器
	Sensorvalue =  new int[MyMotorNumbers];
	lastvalue = new int[MyMotorNumbers];
	for (int i = 0; i < MyMotorNumbers; ++i)
	{
	 	lastvalue[i] = -1;
	}

}

//------------run -----------------------------------------------------------------------
//通过电压，功率等使电机转动
void Control_Motors::RunMotors(int Pwr)//单电机
{
	for (int i = 0; i < MyMotorNumbers; ++i)
	{
		MyMotorList[i].spin(vex::directionType::fwd, Pwr, MyVelocityUnits);
	}
}

void Control_Motors::RunMotors(int *Pwr)//多电机
{
	for (int i = 0; i < MyMotorNumbers; ++i)
	{
		MyMotorList[i].spin(vex::directionType::fwd, Pwr[i], MyVelocityUnits);
	}
}

void Control_Motors::RunMotors(int Pwr,vex::velocityUnits MyVel)
{
	for (int i = 0; i < MyMotorNumbers; ++i)
	{
		MyMotorList[i].spin(vex::directionType::fwd, Pwr, MyVel);
	}
}

void Control_Motors::RunMotors(int *Pwr,vex::velocityUnits MyVel)
{
	for (int i = 0; i < MyMotorNumbers; ++i)
	{
		MyMotorList[i].spin(vex::directionType::fwd, Pwr[i], MyVel);
	}
}

void Control_Motors::RunMotors(double Vol, vex::voltageUnits Myvoltage)
{
  for(int i = 0;  i < MyMotorNumbers; ++i)
  {
    MyMotorList[i].spin(vex::directionType::fwd, Vol, Myvoltage);
  }
}

void Control_Motors::RunMotors(double *Vol, vex::voltageUnits Myvoltage)
{
  for(int i = 0;  i < MyMotorNumbers; ++i)
  {
    MyMotorList[i].spin(vex::directionType::fwd, Vol[i], Myvoltage);
  }
}

//remote mode-----------------------------------------------------------------------------
//通过电机（组）前后方向功率控制电机
void Control_Motors::RemoteMotors(int Pwr)
{
	if((*RunFwd).pressing())		RunMotors(Pwr);
	else if((*RunRev).pressing())	RunMotors(-Pwr);
	else							StopMotors();

	#if Control_Motors_DEBUG
		ShowMotorValue(MotorShowLine);
	#endif
}

void Control_Motors::RemoteMotors(int PwrFwd,int PwrRev)
{
	if((*RunFwd).pressing())		RunMotors(PwrFwd);
	else if((*RunRev).pressing())	RunMotors(PwrRev);
	else							StopMotors();

	#if Control_Motors_DEBUG
		ShowMotorValue(MotorShowLine);
	#endif
}

void Control_Motors::RemoteMotors(int *PwrFwd,int *PwrRev)
{
	if((*RunFwd).pressing())		RunMotors(PwrFwd);
	else if((*RunRev).pressing())	RunMotors(PwrRev);
	else							StopMotors();

	#if Control_Motors_DEBUG
		ShowMotorValue(MotorShowLine);
	#endif
}

//run motor rotation, defualt mode rotation-->deg,  user can change mode with function==>"SetMotorsRotation(int value,vex::rotationUnits RotationUnits)"
//the function just give command to the motor,the robot can do other function at sametimes
//转向特定角度
void Control_Motors::RunMotorsRotation(double RotationValue, int PwrOfMotor)
{
	SetMotorsRotation(0);
	for (int i = 0; i < MyMotorNumbers; ++i)
	{
		MyMotorList[i].rotateFor(RotationValue,MyRotationUnits,PwrOfMotor,MyVelocityUnits,false);
	}
}

//停止所有电机
void Control_Motors::StopMotors(void)
{
	for (int i = 0; i < MyMotorNumbers; ++i)	MyMotorList[i].stop();
}

//set----------------------------------------------------------
//设置停止模式
void Control_Motors::SetStopMode(vex::brakeType BreakMode)
{
	MyBreakMode = BreakMode;
	SetStopMode();
}

//设置电机多长时间未转到指定角度所使用的最长时间，如未完成则停止
void Control_Motors::SetTimeOut(int TimeMsValue)
{
	for (int i = 0; i < MyMotorNumbers; ++i)
	{
		MyMotorList[i].setTimeout(TimeMsValue,MyTimeUnits);
	}
}

//设置电机名称
void Control_Motors::SetMotorsName(char *name)
{
	MyMotorsName = name;

	#if Control_Motors_DEBUG
		printMotorName();
	#endif
}

//设置最大扭矩
void Control_Motors::SetMaxTorque(int percent)
{
  for(int i = 0; i < MyMotorNumbers; ++i)
  {
    MyMotorList[i].setMaxTorque(percent, vex::percent);
  }
}

//设置电机角度
void Control_Motors::SetMotorsRotation(int value)
{
	SetMotorsRotation(value,MyRotationUnits);
}

//设置电机角度
void Control_Motors::SetMotorsRotation(int value,vex::rotationUnits RotationUnits)
{
	for (int i = 0; i < MyMotorNumbers; ++i)
	{
		if(value != 0)		MyMotorList[i].setRotation(value,RotationUnits);
		else				MyMotorList[i].resetRotation();
	}

	#if Control_Motors_DEBUG
		ShowMotorValue(MotorShowLine);
	#endif
}

//获取传感器角度
int* Control_Motors::GetSensorValue(void)
{
	GetRotationValue();
	return Sensorvalue;
}

//获取转速
int Control_Motors::GetRpm(int motorNumber)
{
  int val;

  val = MyMotorList[motorNumber - 1].velocity(vex::velocityUnits::rpm);

  return val;
}

//获取速度
int Control_Motors::GetSpeed(int motorNumber)
{
  int val;

  val = MyMotorList[motorNumber - 1].velocity(vex::velocityUnits::pct);

  return val;
}

//set encoder class----------------------------------------------------------
//设置编码器
void Control_Motors::SetMyEncoder(vex::encoder *Encoder)
{
	MyEncoder = Encoder;
	(*MyEncoder).resetRotation();
}

//获取编码器角度
int Control_Motors::GetEncoderValue_Deg(void)
{
	return (*MyEncoder).rotation(vex::rotationUnits::deg);
}


/*protected**********************************************************************************************************************/
//创建新电机（组）
void Control_Motors::CreatMotors(int *MotorList)
{
	 MyMotorList = (vex::motor*) operator new  (sizeof(vex::motor) * MyMotorNumbers);

	 for (int i = 0; i < MyMotorNumbers; ++i)
	 {
	 	int32_t port = MotorList[i*3] - 1; 
	 	vex::gearSetting gear = vex::gearSetting(MotorList[i*3+1]);
	 	bool head = bool(MotorList[i*3+2]);
	 	new (MyMotorList+i) vex::motor(port,gear,head);
	 }
}

//设置停止模式
void Control_Motors::SetStopMode(void)
{
	for(int i = 0; i < MyMotorNumbers;++i)
	{
		MyMotorList[i].setStopping(MyBreakMode);
	}

	#if Control_Motors_DEBUG
		printStopMode();
	#endif
}

//获取角度
void Control_Motors::GetRotationValue(void)
{
	for (int i = 0; i < MyMotorNumbers; ++i)
	{
		Sensorvalue[i] = MyMotorList[i].rotation(MyRotationUnits);
	}
}

//debug:public**********************************************************************************************************
//调试模式
#if Control_Motors_DEBUG
void Control_Motors::ShowDebugData(int StartLine,int StartList)
{
	Control_Motors_DEBUG_LINE = StartLine;
	Control_Motors_DEBUG_LIST = StartList;

	if(setupFlag == false) setupFlag = true; 

	//print motor name
	printMotorName();
	//print stip mode
	printStopMode();
	//print remote mode
	printRemoteMode();
	//
	ShowMotorValue(MotorShowLine);

}

void Control_Motors::ShowMotorValue(int startLine)
{
	if(setupFlag == true)
	{
		int list;

		GetRotationValue();

		for (int i = 0; i < MyMotorNumbers; ++i)
		{
			int line = Control_Motors_DEBUG_LINE + startLine - 1 + i/2;
			
			if(i % 2 == 0) 	list = Control_Motors_DEBUG_LIST;
			else 			list = Control_Motors_DEBUG_LIST + 10; 

			if(lastvalue[i] != Sensorvalue[i])
			{
				Brain.Screen.setCursor(line,list);
				Brain.Screen.print("M%d:%5d ",i+1,Sensorvalue[i]);
				lastvalue[i] = Sensorvalue[i];
			}
		}
	}
}


void Control_Motors::printMotorName(void)
{
	if(setupFlag == true)
	{
		Brain.Screen.setCursor(Control_Motors_DEBUG_LINE,Control_Motors_DEBUG_LIST);
		Brain.Screen.print("Mode:%-20s",MyMotorsName);
	}
}

void Control_Motors::printStopMode(void)
{
	if(setupFlag == true)
	{
		char stopMode[3][6] = {
			"coast",
			"brake",
			"hold "
		};

	    Brain.Screen.setCursor(Control_Motors_DEBUG_LINE + 1,Control_Motors_DEBUG_LIST);
	    Brain.Screen.print("Stop:%s",stopMode[int(MyBreakMode)]);
	}
}

void Control_Motors::printRemoteMode(void)
{
	Brain.Screen.setCursor(Control_Motors_DEBUG_LINE + 1,Control_Motors_DEBUG_LIST + 12);
		
	if(RemoteMode)		Brain.Screen.print("Remote: T");
	else                Brain.Screen.print("Remote: F");

}
#endif