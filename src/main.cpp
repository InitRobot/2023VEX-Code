/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Victor                                                    */
/*    Created:      2023/10/17 18:34:36                                       */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

//定义电压上限
const int VOLTAGE3=128;
const int VOLTAGE5=12800;

//定义intake模式
int intake_mode=0;//0：无模式，1：暂存，2：发射

//定义intake方向
int intake_direction=2;//0：前，1：后，2：停

//定义粽球距离(mm)
float ball_distance;

// A global instance of competition
competition Competition;

//---------------------------------所有初始化(电机，传感器……)

//视觉传感器
using signature = vision::signature;
using code = vision::code;

/*vex-vision-config:begin*/
//-------------------------------------------------------------------------下一行后参数无法理解，抄的code里的（此文件在桌面）-------------------------------------------
vision::signature Vision_BLUE_BALL = vision::signature(1, -2705, -1873, -2289, 7615, 10485, 9050, 2.1, 0);
vision VisionSensor = vision(PORT17, 50, Vision_BLUE_BALL);
/*vex-vision-config:end*/

//屏幕设置
brain  Brain;

//controller
controller Controller1 = controller(primary);

//distance_sensor
distance distance_sensor = distance(PORT18);

//classis
motor classis_left_1 = motor(PORT1, ratio18_1, false);
motor classis_left_2 = motor(PORT12, ratio18_1, true);
motor_group classis_left = motor_group(classis_left_1, classis_left_2);                        //bottom_l
motor classis_right_1 = motor(PORT2, ratio18_1, false);
motor classis_right_2 = motor(PORT13, ratio18_1, true);
motor_group classis_right = motor_group(classis_right_1, classis_right_2);                       //bottom_r
motor classis_horizontal = motor(PORT3, ratio18_1, false);
inertial DrivetrainInertial = inertial(PORT6);
smartdrive Drivetrain = smartdrive(classis_left, classis_right, DrivetrainInertial, 319.19, 320, 40, mm, 1);

//launcher
motor launcher_left = motor(PORT4, ratio36_1, false);                    //right_leftMotorA
motor launcher_right = motor(PORT5, ratio36_1, true);                           //right_leftMotorB
motor_group launcher = motor_group(launcher_left, launcher_right);

//intake
motor intake_left = motor(PORT8, ratio18_1, false);                                 //rotate_left
motor intake_right = motor(PORT9, ratio18_1, true);                                     //rotate_right
motor_group intake = motor_group(intake_left, intake_right);                              //rotate
//motor_group right_left = motor_group(right_leftMotorA, right_leftMotorB);

// VEXcode generated functions
  // define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;


float sensitivity = 0.5;//range:(0,1]...........................................................................require seting<<<<<<<<<<<<<<<<<<<-----

//The followings are to prevent over voltaging on one side, which leads to a lack of rotation while at high speed.
void classis_move(float left_volt, float right_volt, float horizontal_volt)
{
    float post_classis_left_volt = left_volt;
    float post_classis_right_volt = right_volt;

    if (left_volt > VOLTAGE5)
    {
        post_classis_left_volt = VOLTAGE5;
        post_classis_right_volt = post_classis_right_volt / post_classis_left_volt * VOLTAGE5;
    }
    else if (right_volt > VOLTAGE5)
    {
        post_classis_right_volt = VOLTAGE5;
        post_classis_left_volt = post_classis_left_volt / post_classis_right_volt * VOLTAGE5;
    }

    classis_left.spin(forward, post_classis_left_volt, voltageUnits::mV);
    classis_right.spin(reverse, post_classis_right_volt, voltageUnits::mV);
    classis_horizontal.spin(forward, horizontal_volt, voltageUnits::mV);
}

//定义函数

//intake方向控制
void intake_forward()
{
    intake.spin(forward, -VOLTAGE5, voltageUnits::mV);
    intake_direction=0;
}

void intake_backward()
{
    intake.spin(forward, VOLTAGE5, voltageUnits::mV);
    intake_direction=1;
}

void intake_stop()
{
    intake.spin(forward, 0, voltageUnits::mV);
    intake_direction=2;
}

//intake&launcher状态转换
void manual_mode()
{
    intake_mode=0;
    intake_stop();
}

void storage_mode()
{
    intake_mode=1;
    intake_stop();
}

void launch_mode()
{
    intake_mode=2;
}

//launcher方向控制
void launcher_forward()
{
    launcher.spin(forward, VOLTAGE5, voltageUnits::mV);
}

void launcher_stop()
{
    launcher.spin(forward, 0, voltageUnits::mV);
}

//所有应用于自动之前的初始化程序
void pre_auton(void)
{
    //底盘初始化
    DrivetrainInertial.calibrate();
}

//自动程序
void autonomous(void)
{
    //底盘初始化
    DrivetrainInertial.calibrate();

}

//手动程序
void usercontrol(void)
{
    //底盘初始化
    DrivetrainInertial.calibrate();

    int times = 0;
    int launch = 0;
    while (1)
    {
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

        ball_distance = distance_sensor.objectDistance(mm);
        Brain.Screen.newLine();
        Brain.Screen.print(distance_sensor.objectDistance(mm));
        //end distance

        //axis position
        float axis1 = Controller1.Axis1.position(percent);
        float axis2 = Controller1.Axis2.position(percent);
        float axis3 = Controller1.Axis3.position(percent);
        float axis4 = Controller1.Axis4.position(percent);

        //=========================================intake=================================
        //手动操控
        if(intake_mode!=1)
        {
            //按住R1 intake向上
            Controller1.ButtonR1.pressed(intake_forward);
            Controller1.ButtonR1.released(intake_stop);
            //按住R2 intake向下
            Controller1.ButtonR2.pressed(intake_backward);
            Controller1.ButtonR2.released(intake_stop);           
        }

        //检测模式更改
        Controller1.ButtonY.pressed(manual_mode);
        Controller1.ButtonX.pressed(storage_mode);
        Controller1.ButtonA.pressed(launch_mode);
        
        //对应模式代码
        Controller1.Screen.clearScreen();//在手柄屏幕上输出模式
        Controller1.Screen.print("%d:",intake_mode);
        switch(intake_mode)
        {
            case 0://无模式
            {
                Controller1.Screen.print("Manual");
                break;
            }
            case 1://暂存
            {
                Controller1.Screen.print("Storage");
                Controller1.ButtonR1.pressed(intake_forward);
                Controller1.ButtonR2.pressed(intake_backward);
                ball_distance = distance_sensor.objectDistance(mm);
                //当球离传感器400mm以内时阻止球向上
                if (ball_distance < 400 && intake_direction == 0)
                {
                    intake.spin(forward,0, voltageUnits::mV);
                }
                break;
            }
            case 2://发射
            {
                Controller1.Screen.print("Launch");
                //intake始终向上
                intake.spin(forward, -VOLTAGE5, voltageUnits::mV);
                ball_distance = distance_sensor.objectDistance(mm);
                //球距小于等于175mm时发射
                if (ball_distance <= 175)
                {
                    ball_distance=distance_sensor.objectDistance(mm);
                    launcher.spin(forward, VOLTAGE5, voltageUnits::mV);
                    wait(700, msec);
                    Controller1.Screen.clearScreen();
                    Controller1.Screen.print("%d",ball_distance);
                    break;
                }
                else launcher.spin(forward, 0, voltageUnits::mV);
                break;
            }
            default: Controller1.Screen.print("ERR!");//模式不在[0,2]内则报错
        }
        Controller1.Screen.newLine();
        //-------------------------------------------------------end intake-------------------------

        
        //============================================launcher==========================
        //按住L1时launcher往下
        Controller1.ButtonL1.pressed(launcher_forward);
        Controller1.ButtonL1.released(launcher_stop);
        //--------------------------------------------end launcher--------------------------------------------

        
        //=====================================================classis==================================================

        //aim
        if (Controller1.ButtonL2.pressing())
        {
            axis1 = 0;
            axis1 = err * 1;
        }//end aim

        float pre_classis_left_volt = VOLTAGE3 * axis3 + VOLTAGE3 * axis1 * sensitivity;
        float pre_classis_right_volt = VOLTAGE3 * axis3 - VOLTAGE3 * axis1 * sensitivity;
        float pre_classis_horizontal_volt = VOLTAGE3 * axis4;
        classis_move(pre_classis_left_volt, pre_classis_right_volt, pre_classis_horizontal_volt);
        //-------------------------------------------------end classis-------------------------------------------------------


        wait(20, msec); // Sleep the task for a short amount of time to
        // prevent wasted resources.
    }
}


// Main will set up the competition functions and callbacks.
int main()
{
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true)
    {
        wait(100, msec);
    }
}