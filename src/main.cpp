#include "vex.h"
#include "basic-functions.h"
#include "parameters.h"
#include "autonomous.h"
#include "my-timer.h"
#include "controller.h"
#include "cstdlib"
#include "iostream"
#include "GPS.h"
#include "sensors.h"
#include "adjusment.h"

using namespace vex;
competition Competition;

void pre_auton(void) {
  vexcodeInit();
}
】‘【’

void autonomous(void)
{
  auton_one();
}

void usercontrol(void) {
  // User control code here, inside the loop
  bool is_base_locked = false;
  unlockBase();//刹车滑行
  while (1)
  {
    // Controller Input
    defineController();
    // Base Movement Control
    A3 = A3 * abs(A3) / 100.0 * SENSITIVITY_TURN;//对转弯做非线性处理
    if (std::abs(A3) < JOYSTICK_DEADZONE)
      A3 = 0;
    if (std::abs(A1) < JOYSTICK_DEADZONE)
      A1 = 0;
    if (std::abs(0-A1 - A3) > MOVEMENT_LOWER_LIMIT)
      moveLeft(0-A1 - A3);
    else
      unlockLeft();
    if (std::abs(0-A3 + A1) > MOVEMENT_LOWER_LIMIT)
      moveRight(0-A3 + A1);
    else
      unlockRight();

    //滚筒移动
    if(Controller1.ButtonR1.pressing()) {
      RollerSpin(VOLTAGE5);
    } else if(Controller1.ButtonR2.pressing()) {
      RollerSpin(-VOLTAGE5);
    } else {
      RollerSpin(0);
    }

    //弹射触发
    if(Controller1.ButtonL1.pressing()) {
      Shoot(1);
    } else {
      Shoot(0);
    }
    
    //抬升升起
    if(UP && !last_UP) {
      liftUp();
    }
  }

  // Print on brain
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Heading: %3.2f", my_sensors.getBaseHeading());
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Forward Position: %4.1f", my_sensors.getBaseForwardPos());
  Brain.Screen.setCursor(3, 1);
  this_thread::sleep_for(5);
}

int main() {
  thread AutonSensors(autonSensors);
  thread AutonGps(autonGPS);
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}