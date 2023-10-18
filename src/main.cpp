/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       21348                                                     */
/*    Created:      2023/9/30 15:19:58                                        */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

  using signature = vision::signature;
  using code = vision::code;

  // A global instance of brain used for printing to the V5 Brain screen
  brain  Brain;

  // VEXcode device constructors
  
  //controller
  controller Controller1 = controller(primary);                             //


  
  /*vex-vision-config:begin*/
  //-------------------------------------------------------------------------下一行后参数无法理解，抄的code里的（此文件在桌面）-------------------------------------------
  vision::signature Vision_BLUE_BALL = vision::signature (1, -2705, -1873, -2289,7615, 10485, 9050,2.1, 0);
  vision VisionSensor = vision (PORT17, 50, Vision_BLUE_BALL);
  /*vex-vision-config:end*/
  
  //distance_sensor
  distance distance_sensor = distance(PORT18);

  //classis
  motor classis_left = motor(PORT1, ratio18_1, false);                        //bottom_l
  motor classis_right = motor(PORT2, ratio18_1, false);                       //bottom_r
  motor classis_horizontal = motor(PORT3, ratio18_1, false);                  //Motor3

  //launcher
  motor launcher_left = motor(PORT4, ratio36_1, false);                    //right_leftMotorA
  motor launcher_right = motor(PORT5, ratio36_1, true);                           //right_leftMotorB
  motor_group launcher = motor_group(launcher_left, launcher_right);                    //shoot

  //intake
  motor intake_left = motor(PORT8, ratio18_1, false);                                 //rotate_left
  motor intake_right = motor(PORT9, ratio18_1, true);                                     //rotate_right
  motor_group intake = motor_group(intake_left, intake_right);                              //rotate
  //motor_group right_left = motor_group(right_leftMotorA, right_leftMotorB);

  // VEXcode generated functions
  // define variable for remote controller enable/disable
  bool RemoteControlCodeEnabled = true;
// A global instance of competition
competition Competition;

float sensitivity = 0.5;//range:(0,1]...........................................................................require seting<<<<<<<<<<<<<<<<<<<-----

//The followings are to prevent over voltaging on one side, which leads to a lack of rotation while at high speed.
void classis_move(float left_volt, float right_volt, float horizontal_volt){
  float post_classis_left_volt = left_volt;
  float post_classis_right_volt = right_volt;

  if (left_volt > 12000)
  {
    post_classis_left_volt = 12000;
    post_classis_right_volt = post_classis_right_volt / post_classis_left_volt * 12000;
  }else if (right_volt > 12000)
  {
    post_classis_right_volt = 12000;
    post_classis_left_volt = post_classis_left_volt / post_classis_right_volt * 12000;
  }
  
  classis_left.spin(forward, post_classis_left_volt, voltageUnits::mV);
  classis_right.spin(reverse, post_classis_right_volt, voltageUnits::mV);
  classis_horizontal.spin(forward, horizontal_volt, voltageUnits::mV);
}

void classis_move_with_speed_in_direction(float speed, float rotation, float direction){
  //----------------------------------------------------------------------------------------------------required
}

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  classis_move(12000,12000,0);
  intake.spin(reverse, 12000, voltageUnits::mV);
  wait(600, msec);
  launcher.spin(forward,12000,voltageUnits::mV);
  
  wait(1400, msec);
  //launcher.spin(forward,0,voltageUnits::mV);
  classis_move(-12000,-12000,0);
  wait(1100, msec);
  launcher.spin(forward,0,voltageUnits::mV);
  classis_move(0,0,0);
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  
  float intake_spin = -12000;
  int ball = 0;//0:stop,1:up,-1:down
  int times = 0;
  int launch = 0;
  while (1) {
    Brain.Screen.clearScreen();



    //vision(show blue ball place)
    VisionSensor.takeSnapshot(Vision_BLUE_BALL);
    times++;
    Brain.Screen.setCursor(1, 1);
    /*Brain.Screen.print("N: %d", VisionSensor.objectCount);
    Brain.Screen.newLine();
    for(int i = 0; i < VisionSensor.objectCount; i++) {
      Brain.Screen.print("X: %d", VisionSensor.objects[i].centerX);
      Brain.Screen.newLine();
      Brain.Screen.print("Y: %d", VisionSensor.objects[i].centerY);
      Brain.Screen.newLine();
    }*/
    int err = VisionSensor.largestObject.centerX - 160;
    Brain.Screen.print("X: %d", err);
    Brain.Screen.newLine();
    Brain.Screen.print(times);
    //end vision

    float ball_distance = distance_sensor.objectDistance(mm);
    Brain.Screen.newLine();
    Brain.Screen.print(distance_sensor.objectDistance(mm));
    //end distance

    //axis position
    float axis1 = Controller1.Axis1.position(percent);
    float axis2 = Controller1.Axis2.position(percent);
    float axis3 = Controller1.Axis3.position(percent);
    float axis4 = Controller1.Axis4.position(percent);
    


    //=========================================intake=================================
    //float intake_spin = 0;
    
    if(Controller1.ButtonR2.pressing())
    {
      ball = -1;
    }
    if(Controller1.ButtonA.pressing())  {
      ball = 0;
    }  
    if(Controller1.ButtonR1.pressing())
    {
        ball = 1;
    }
    if (ball_distance <=200 && ball == 1)
    {
      ball = 0;
    }
    
    
    //-------------------------------------------------------end intake-------------------------




    //============================================launcher==========================
    //launch = 0
    float launcher_spin = 12000;
    if(Controller1.ButtonL1.pressing())
    {
        launch = 1;
        ball = 1;
    }
    if (launch == 1 && ball_distance >=200)
    {
      launch = 0;
      ball = 0;
    }
    
    launcher.spin(forward,launcher_spin * launch,voltageUnits::mV);
    intake.spin(forward, intake_spin * ball, voltageUnits::mV);
    //launcher.spin(forward, 128*axis3, voltageUnits::mV);
    //--------------------------------------------end launcher--------------------------------------------



    //=====================================================classis==================================================
    
    //aim
    if (Controller1.ButtonL2.pressing())
    {
      axis1 = 0;
      axis1 = err * 1;
    }//end aim
    
    float pre_classis_left_volt = 120*axis3+120*axis1*sensitivity;
    float pre_classis_right_volt = 120*axis3-120*axis1*sensitivity;
    float pre_classis_horizontal_volt = 120*axis4;
    classis_move(pre_classis_left_volt, pre_classis_right_volt,pre_classis_horizontal_volt);
    //-------------------------------------------------end classis-------------------------------------------------------

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
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
