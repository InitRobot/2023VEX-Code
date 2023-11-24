/*
Deshitting_1
  20231122t17:53
  参与人员：陈佳天，黄敏达，李杰瑞，王一赫，瞿子涵

*/


#include "Remote_Control.h"
#include "MyAutoPro.h"

void RemoteSetUp(void)
{
  //设置电机最大扭矩
  MyVehicle.SetMaxTorque(100);
  //设置电机角度???                                                           <---Unsure
  MyVehicle.SetMotorsRotation(0, vex::rotationUnits::deg);
}




//-----------------以下为电机驱动函数
/*
电机驱动函数框架：
void RunMy_____(double _____Vol(,......))//个数n
{
  _____Vol *=  0.12;
  ......

  ______.RunMotors_____Vol, vex::voltageUnits::volt);
}
*/

//底盘控制
void RunMyVehicle(double leftVol, double rightVol)
{
  double Vol[4];

  leftVol *=  0.12;
  rightVol *= 0.12;

  Vol[0] = leftVol;Vol[1] = leftVol;
  Vol[2] = rightVol;Vol[3] = rightVol;

  MyVehicle.RunMotors(Vol, vex::voltageUnits::volt);
}


//其他电机驱动
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
//-----------------以上为电机驱动函数




//显示队伍编号
void ShowTeamNum(char *Num)
{
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(vex::fontType::mono60);
    Brain.Screen.printAt(275,80, "TEAM");
    Brain.Screen.printAt(250,140, Num);
}

//my remote control
void Remote_vehicle_control(int VehicleSpeed)//VehicleSpeed最快速度                           <--
{
  static int Axis3threathHold = VehicleSpeed;//将一个名为"VehicleSpeed"的变量的值赋给了名为"Axis3threathHold"的静态整型变量(只会被初始化一次，该函数在调用过程中，其值保持不变。)
  static int LastA3 = 0;
  static int Axis1threathHold = VehicleSpeed;
  static int LastA1 = 0;//                                                               <--

  int YWayVal = Controller1.Axis3.position(vex::percentUnits::pct) * Axis3threathHold /100.0;//按遥感角度分配速度百分比
  int XWayVal = Controller1.Axis1.position(vex::percentUnits::pct);
  XWayVal = ((XWayVal * abs(XWayVal)) *1.0 / 100)  * Axis1threathHold / 100.0; //更好适应快速转向与慢速转向间的转换()
    
  double MyrightVol = (YWayVal - XWayVal) ;   
  double MyleftVol =  (YWayVal + XWayVal) ;//左右底盘速度百分比

  RunMyVehicle(MyleftVol, MyrightVol);//底盘运动
  
  //Show Detail                                                                           <--
  if(Controller1.ButtonUp.pressing() && Axis3threathHold != 100)    Axis3threathHold = 100;
  if(Controller1.ButtonDown.pressing()&& Axis3threathHold != VehicleSpeed)    Axis3threathHold = VehicleSpeed;
  if(Controller1.ButtonLeft.pressing() && Axis1threathHold != VehicleSpeed)   Axis1threathHold = VehicleSpeed;
  if(Controller1.ButtonRight.pressing() && Axis1threathHold != 100) Axis1threathHold = 100;

  if(LastA3 != Axis3threathHold)//显示y轴Axis3threathHold
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


  //以下为特别键位的功能
  //In Take Control
  double InTakeVol = Controller1.ButtonR1.pressing()*100 - Controller1.ButtonR2.pressing() * 100;
  RunMyPaw(InTakeVol);

  //Shoot Control
  int static Conv = 100;
  int static LastVal = 0;
  double ShootV = Conv / 100.0 *(Controller1.ButtonL1.pressing()*100-Controller1.ButtonL2.pressing()*100);
  RunMyShoot(ShootV);
  //以上为特别键位的功能


  //改变发射速度
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
