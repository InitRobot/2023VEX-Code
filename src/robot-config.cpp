#include "vex.h"
#include "parameters.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);

#ifdef ROBOT_ONE
  motor Motor_BaseLF = motor(PORT1, ratio6_1, true);
  motor Motor_BaseLM = motor(PORT2, ratio6_1, false);//LBU
  motor Motor_BaseLB = motor(PORT3, ratio6_1, true);//LBD
  motor Motor_BaseRF = motor(PORT4, ratio6_1, true);
  motor Motor_BaseRM = motor(PORT5, ratio6_1, false);//RBU
  motor Motor_BaseRB = motor(PORT9, ratio6_1, true);//RBD
  motor Motor_Roller = motor(PORT12, ratio18_1, true);
  inertial IMU = inertial(PORT10);
  motor_group BaseL= motor_group(Motor_BaseLB, Motor_BaseLF, Motor_BaseLM);
  motor_group BaseR= motor_group(Motor_BaseRB, Motor_BaseRF, Motor_BaseRM);
  smartdrive Drivetrain = smartdrive(BaseL, BaseR, IMU, 0, 320, 40, mm, 1);//垂直距离、轮距、轴距
  motor Motor_Shoot = motor(PORT11, ratio6_1, false);
#endif

#ifdef ROBOT_TWO
  
#endif

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

void vexcodeInit(void) {
  IMU.startCalibration();
  while (IMU.isCalibrating()) {
    this_thread::sleep_for(5);
  }
  //Controller1.Screen.setCursor(5, 1);
  //Controller1.Screen.print("%19s", "CA");
  Controller1.Screen.setCursor(5, 1);
  Controller1.Screen.print("%10s", "l_6_2");
  
  //show auton_strategy
  switch (auton_strategy) {
  case 0:
    Controller1.Screen.setCursor(5, 1);
    Controller1.Screen.print("%10s", "auto one");
    break;
  case 1:
    Controller1.Screen.setCursor(5, 1);
    Controller1.Screen.print("%10s", "auto two");
    break;
  case 2:
    Controller1.Screen.setCursor(5, 1);
    Controller1.Screen.print("%10s", "auto three");
    break;
  case 3:
    Controller1.Screen.setCursor(5, 1);
    Controller1.Screen.print("%10s", "auto four");
    break;
  case 4:
    Controller1.Screen.setCursor(5, 1);
    Controller1.Screen.print("%10s", "yousb");
    break;
  }

  // Brain.Screen.setCursor(12, 1);
  // Brain.Screen.print("Competition Version");
}