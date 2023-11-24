#include "Remote_Control.h"
#include "MyAutoPro.h"

void RemoteSetUp(void)
{
  MyVehicle.SetMaxTorque(100);
  MyVehicle.SetMotorsRotation(0, vex::rotationUnits::deg);
}

void RunMyVehicle(double leftVol, double rightVol)
{
  double Vol[4];

  leftVol *=  0.12;
  rightVol *= 0.12;

  Vol[0] = leftVol;Vol[1] = leftVol;
  Vol[2] = rightVol;Vol[3] = rightVol;

  MyVehicle.RunMotors(Vol, vex::voltageUnits::volt);
}

void RunMyPaw(double PawVol)
{
  MyPaw.RunMotors(PawVol * 0.12, vex::voltageUnits::volt);
}

void RunMyShoot(double ShootVol)
{
  ShootVol *= 0.12;
  InTakeRoll.RunMotors( ShootVol , vex::voltageUnits::volt);
  OutPutRoll.RunMotors( ShootVol, vex::voltageUnits::volt);
}

void ShowTeamNum(char *Num)
{
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(vex::fontType::mono60);
    Brain.Screen.printAt(275,80, "TEAM");
    Brain.Screen.printAt(250,140, Num);
}

//my remote control
void Remote_vehicle_control(int VehicleSpeed)
{
  static int Axis3threathHold = VehicleSpeed;
  static int LastA3 = 0;
  static int Axis1threathHold = VehicleSpeed;
  static int LastA1 = 0;

  int YWayVal = Controller1.Axis3.position(vex::percentUnits::pct) * Axis3threathHold /100.0;
  int XWayVal = Controller1.Axis1.position(vex::percentUnits::pct);
  XWayVal = ((XWayVal * abs(XWayVal)) *1.0 / 100)  * Axis1threathHold / 100.0; 
    
  double MyrightVol = (YWayVal - XWayVal) ;   
  double MyleftVol =  (YWayVal + XWayVal) ;

  RunMyVehicle(MyleftVol, MyrightVol);
  
  //Show Detail
  if(Controller1.ButtonUp.pressing() && Axis3threathHold != 100)    Axis3threathHold = 100;
  if(Controller1.ButtonDown.pressing()&& Axis3threathHold != VehicleSpeed)    Axis3threathHold = VehicleSpeed;
  if(Controller1.ButtonLeft.pressing() && Axis1threathHold != VehicleSpeed)   Axis1threathHold = VehicleSpeed;
  if(Controller1.ButtonRight.pressing() && Axis1threathHold != 100) Axis1threathHold = 100;

  if(LastA3 != Axis3threathHold)
  {
    Controller1.Screen.setCursor(4, 1);
    Controller1.Screen.print("Y:");
    Controller1.Screen.print("%3d",Axis3threathHold);
    Controller1.Screen.print("%%");
    LastA3 = Axis3threathHold;
  }

  if(LastA1 != Axis1threathHold)
  {
    Controller1.Screen.setCursor(4, 8);
    Controller1.Screen.print("X:");
    Controller1.Screen.print("%3d",Axis1threathHold);
    Controller1.Screen.print("%%");
    LastA1 = Axis1threathHold;
  }
}

void MyRemote(int VehicleSpeed,int RollSpeed)
{
  Remote_vehicle_control(VehicleSpeed);

  //In Take Control
  double InTakeVol = Controller1.ButtonR1.pressing()*100 - Controller1.ButtonR2.pressing() * 100;
  RunMyPaw(InTakeVol);

  //Shoot Control
  int static Conv = 100;
  int static LastVal = 0;
  double ShootV = Conv / 100.0 *(Controller1.ButtonL1.pressing()*100-Controller1.ButtonL2.pressing()*100);
  RunMyShoot(ShootV);
  
  //change speed
  if(Controller1.ButtonX.pressing())Conv=100;
  if(Controller1.ButtonY.pressing())Conv=RollSpeed;

  if(Conv != LastVal)
  {
    Controller1.Screen.setCursor(4,15);
    Controller1.Screen.print("S:");
    Controller1.Screen.print("%3d",Conv);
    Controller1.Screen.print("%% ");
    LastVal = Conv;
  }
  //wait(TaskSleepMs, msec);
}
