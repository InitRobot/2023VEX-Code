#include "MyAutoPro.h"

/*-----------------------------define sensor & motor---------------------------------------*/
//sensor
/*gyro MyGyro = gyro(Brain.ThreeWirePort.H);
line MyLineTracker = line(Brain.ThreeWirePort.B);*/
//PAW
               //port 16-gear head
int PawMotor[] = {2,1,0,
                  18,1,1};
Control_Motors MyPaw = Control_Motors(PawMotor,2);

/*vehicle*/                    
                    //port 16-gear head
int VehicleMotor[] = {13,1,0,  //port 9 left front
                      14,1,1,  //port 14 left rear
                      12,1,1,  //port 3 right front
                      20,1,0}; //port 4 right rear
Control_Motors MyVehicle = Control_Motors(VehicleMotor,4);

//InTake Roll
                    //port 32-gear head
int InTakeMotor[] = {10,2,0};
Control_Motors InTakeRoll = Control_Motors(InTakeMotor,1);

//OutPut Roll
                    //port 16-gear head
int OutPutMotor[] = {4,1,0};
Control_Motors OutPutRoll = Control_Motors(OutPutMotor,1);


void  AutoProRight(int LineTrackerValue)
{
  //test function
  //check sensor
  RollInBall(LineTrackerValue, 0);
  RunPaw(-100); //open top
  TurnWithRotation(270, -50, -50);wait(300, msec); RunPaw(0);//go back
  TurnWithRotation(60, 50, -50);wait(200, msec); //turn to middle

  //head to middle
  GoPidDegree(36, 150,0);   MyPaw.RunMotors(12, vex::voltageUnits::volt); //head to middle
  MyVehicle.RunMotors(12,vex::voltageUnits::volt); wait(500, msec); MyVehicle.RunMotors(1);//go ahead and stop
  RollInBall(LineTrackerValue, 1);
  ShootBallOnce(1, 195, LineTrackerValue);
  MyVehicle.StopMotors();
  
  //get second ball
  /*MyPaw.RunMotors(12, vex::voltageUnits::volt);
  MyVehicle.RunMotors(-100);wait(300, msec); MyVehicle.StopMotors(); wait(200, msec);
  MyVehicle.RunMotors(100);wait(200, msec);
  MyVehicle.RunMotors(2); wait(300, msec);
  RollInBall(LineTrackerValue, 1);
  ShootBallOnce(1, 195, LineTrackerValue);*/
  
  //go back turn to another basket
  MyPaw.RunMotors(-12, vex::voltageUnits::volt); 
  TurnWithRotation(730, -80, -80);wait(300, msec);
  MyPaw.StopMotors(); 
  TurnWithRotation(170, -50, 50);wait(200, msec);
  MyPaw.RunMotors(12, vex::voltageUnits::volt);
  GoPidDegree(-50, 400,0);
  MyVehicle.RunMotors(60*.12,vex::voltageUnits::volt); wait(800, msec);MyVehicle.RunMotors(1);
  
  //shoot second Ball
  RollInBall(LineTrackerValue,1);
  MyPaw.RunMotors(-12, vex::voltageUnits::volt);wait(300, msec);
  ShootBallOnce(1, 195, LineTrackerValue);
  MyVehicle.StopMotors();
  
  //go back
  MyPaw.RunMotors(-12, vex::voltageUnits::volt); wait(300, msec);
  TurnWithRotation(200, -80, -80);wait(300, msec);
  MyPaw.StopMotors();
 
  /*
  //Setup robot
  MyPaw.RunMotors(-100, vex::voltageUnits::volt);  wait(200,msec);
  RunPaw(0);  wait(100,msec);
  
  //go ahead
  RunPaw(100);
  GoPidDegree(0,1200);  wait(200,msec);
  RunPaw(0);//get ball
  
  //goback 
  TurnWithRotation(620,-60,-60); //Go back
  wait(200,msec);
  
  //turn left and throw out my ball
  TurnWithRotation(220,-40,40);   wait(200,msec);

  //turn to the basket go ahead to get ball
  TurnWithRotation(100,-40,40); wait(200,msec);
  RunPaw(100);
  GoPidDegree(-135,460);//go ahead get my ball
  wait(200,msec);
  MyVehicle.RunMotors(20*0.12,vex::voltageUnits::volt);  wait(500,msec);
  MyVehicle.RunMotors(10*0.12, vex::voltageUnits::volt);  wait(1000,msec);
  MyVehicle.StopMotors();   RunPaw(0);
  
  //roll out 
  RunPaw(50);
  //RunPaw(0);InTakeRoll.RunMotors(0);
  
  MyVehicle.SetStopMode(vex::brakeType::coast);
  wait(20,msec);
  ShootBallOnce(1,195,LineTrackerValue);
  RunPaw(0);
  wait(500,msec);
  TurnWithRotation(50,-40,-40); 
  */
} 


void RunPaw(int speed)
{
  if(speed == 0)  MyPaw.StopMotors();
  else            MyPaw.RunMotors(speed * 0.12, vex::voltageUnits::volt);

}

//init pro
void AutoSetup(void)
{
  //MyPaw.SetMotorsName("Paw");
  MyGyro.setRotation(0,degrees);
  wait(100,msec);
  MyGyro.setHeading(0,degrees);
  wait(100,msec);

  //motor stop mode
  MyVehicle.SetStopMode(vex::brakeType::brake);
  MyPaw.SetStopMode(vex::brakeType::coast);
  InTakeRoll.SetStopMode(vex::brakeType::brake);
  OutPutRoll.SetStopMode(vex::brakeType::coast);

}

/*show gyro data
void GyroTest(void)
{
  int Myrotation = GyroA.rotation();
  int Myangle = GyroA.heading();
  static int lastro = -100;
  static int lastan = -100;

  if(lastro != Myrotation)
  {
    lastro = Myrotation;
    Brain.Screen.setCursor(1,1);
    Brain.Screen.clearLine();
    Brain.Screen.print("rotation:");
    Brain.Screen.print(Myrotation);
  }
  
  if(lastan != Myangle)
  {
    lastan = Myangle;
    Brain.Screen.setCursor(2,1);
    Brain.Screen.clearLine();
    Brain.Screen.print("angle:");
    Brain.Screen.print(Myangle);
  }
}*/

//adjust head to the Relative 0 degree 
int HeadChange(int head,int nowValue)
{
  nowValue = nowValue - head;

  if(nowValue >= 180)       nowValue = nowValue - 360;
  else if(nowValue < -180) nowValue = nowValue + 360;

  return nowValue;
}

void PIDGyro(int HeadDegree)
{
    int RunTP = 70;
    float kp = 0.27, kd = 2;    //define kp kd value
    
    static int Lasterr = 0;
    int Rotation = MyGyro.rotation();

    int GyroRotation = Rotation % 360;
    if(GyroRotation >= 180)        GyroRotation = GyroRotation - 360;
    else if(GyroRotation < -180)  GyroRotation = GyroRotation + 360;

    //PID cal
    int err = HeadChange(HeadDegree,GyroRotation);
    int Solve = err * kp + (err - Lasterr) * kd;
    Lasterr = err;

    double vehicleSpeed[4];
    vehicleSpeed[0] = (RunTP - Solve) * 0.12;//left
    vehicleSpeed[1] = (RunTP - Solve) * 0.12;
    vehicleSpeed[2] = (RunTP + Solve) * 0.12;//right
    vehicleSpeed[3] = (RunTP + Solve) * 0.12;
    
    //run vehicle
    MyVehicle.RunMotors(vehicleSpeed,vex::voltageUnits::volt);

    //debug data
    /*
    static int lastro = -1;
    if(lastro != Rotation )
    {
      lastro = Rotation; 
      Brain.Screen.setCursor(1,1);
      Brain.Screen.clearLine();
      Brain.Screen.print("rotation:");
      Brain.Screen.print(Rotation);
      
      Brain.Screen.setCursor(2,1);
      Brain.Screen.clearLine();
      Brain.Screen.print("degree:");
      Brain.Screen.print(GyroRotation);

      Brain.Screen.setCursor(3,1);
      Brain.Screen.clearLine();
      Brain.Screen.print("err:");
      Brain.Screen.print(err);
      Brain.Screen.setCursor(3,10);
      Brain.Screen.print("solve:");
      Brain.Screen.print(Solve);

      Brain.Screen.setCursor(4,1);
      Brain.Screen.clearLine();
      Brain.Screen.print("LeftSpeed:");
      Brain.Screen.print(vehicleSpeed[0]);
      Brain.Screen.setCursor(4,17);
      Brain.Screen.print("RightSpeed:");
      Brain.Screen.print(vehicleSpeed[2]);
    
    }*/

}

void GoPidDegree(int head,int degree,int stopflag)
{
  int *value = MyVehicle.GetSensorValue();
  int startvalue = value[0];
  int nowvalue = startvalue;

  while(abs(nowvalue - startvalue) <= degree)
  {
    wait(10,msec);
    PIDGyro(head);
    MyVehicle.GetSensorValue();
    nowvalue = value[0];
  }

  if(stopflag == 1) MyVehicle.StopMotors();
}

//ball roll ---------------------------------------------------------ball roll-----------------
int CheckBall(int checkvalue)
{
  //wait(500, msec);
  int checkflag = 0;
  int val = MyLineTracker.value(vex::analogUnits::range12bit);
  if(val < checkvalue) checkflag = 1;

  /*.debug*/
  static int lastval = -1;
  if(lastval != val)
  {
    Brain.Screen.setCursor(1,1);
    Brain.Screen.clearLine();
    Brain.Screen.print("val:");
    Brain.Screen.print(val);

    Brain.Screen.setCursor(2,1);
    Brain.Screen.clearLine();
    Brain.Screen.print("checkval:");
    Brain.Screen.print(checkvalue);

    Brain.Screen.setCursor(3,1);
    Brain.Screen.clearLine();
    Brain.Screen.print("flag:");
    Brain.Screen.print(checkflag); 
    lastval = val;
  }

  return checkflag;
}
//------------------sensor val---paw run or stop-----------------     
void RollInBall(int SensorVal,int PawRunState)
{
  //check no ball
  if(CheckBall(SensorVal) == 0)
  {
    if(PawRunState == 1) MyPaw.RunMotors(12, vex::voltageUnits::volt);

    InTakeRoll.RunMotors(250,vex::velocityUnits::rpm);
    
    int ms = vex::timer::system();
    int now = ms;

    while(CheckBall(SensorVal) == 0 && (now - ms) < 3000) now = vex::timer::system();

    InTakeRoll.StopMotors();
    if(PawRunState == 1) MyPaw.StopMotors();
  }
}

//wait the motor run to setting rpm
void ShootCheckRPM(int MyRPM)
{
  int rpm,speed = OutPutRoll.GetSpeed(1);
  int starttime = vex::timer::system();
  int now = starttime;
  do{
    rpm = OutPutRoll.GetRpm(1);
    if(speed < 100)    
    {
        ++speed; 
        OutPutRoll.RunMotors(speed * 0.12, vex::voltageUnits::volt);
        wait(10,msec);
    } 
    /*/debug 
    int lastrpm = -1;
    if(lastrpm != rpm)
    {
      Brain.Screen.setCursor(9,1);
      Brain.Screen.clearLine();
      Brain.Screen.print("speed:");
      Brain.Screen.print(speed);

      Brain.Screen.setCursor(8,1);
      Brain.Screen.clearLine();
      Brain.Screen.print("rpm:");
      Brain.Screen.print(rpm);
      lastrpm = rpm;
    }*/
    
  }while(rpm < MyRPM && (now - starttime) < 2500);
  OutPutRoll.RunMotors(12, vex::voltageUnits::volt);

}

//this mode is for 16076A
void ShootBallOnce(bool stopFlag,int ShootValue,int Sensorval)
{
  //wait OutPutMotor to the setspeed
  ShootCheckRPM(ShootValue);  
  wait(500, msec);
  /*
  Brain.Screen.setCursor(5,1);
  Brain.Screen.clearLine();
  Brain.Screen.print("roll up");*/
  
  //roll up ball
  CheckBall(Sensorval);
  InTakeRoll.RunMotors(100 * 0.12,vex::voltageUnits::volt);
  while(CheckBall(Sensorval));
  wait(500,msec);
  InTakeRoll.StopMotors();

  /*
  Brain.Screen.setCursor(6,1);
  Brain.Screen.clearLine();
  Brain.Screen.print("roll out");*/
  //roll out ball
  //while(CheckBall(Sensorval))  InTakeRoll.RunMotors(100 * 0.12,vex::voltageUnits::volt);
  //wait(500,msec);
  //InTakeRoll.StopMotors();

  /*Brain.Screen.setCursor(7,1);
  Brain.Screen.clearLine();
  Brain.Screen.print("done up");*/
  //stop check

  if(stopFlag==1)      OutPutRoll.StopMotors();
}

//this mode is for 16076B
void ShootBallOnce_B(int stopflag,int Sensorval)
{
  InTakeRoll.RunMotors(100 * 0.12,vex::voltageUnits::volt);
  OutPutRoll.RunMotors(100 * 0.12,vex::voltageUnits::volt);

  while(CheckBall(Sensorval) == 0);

  if(stopflag == 1)
  {
    InTakeRoll.StopMotors();
    OutPutRoll.StopMotors();
  }  
}

void TurnWithRotation(int MyRotation,int leftspeed,int rightspeed)
{
  double mspeed[4] = {leftspeed * 0.12,leftspeed * 0.12,rightspeed * 0.12,rightspeed * 0.12};
  int *value = MyVehicle.GetSensorValue();
  int startvalue = value[0];

  MyVehicle.RunMotors(mspeed,vex::voltageUnits::volt);

  int val;  
  do{
    MyVehicle.GetSensorValue();
    val = value[0];
    wait(20,msec);
    /*
    Brain.Screen.setCursor(7,1);
    Brain.Screen.clearLine();
    Brain.Screen.print(val); */

  }while(abs(val-startvalue) < MyRotation);

  MyVehicle.StopMotors();
}



