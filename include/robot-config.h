using namespace vex;
using signature = vision::signature;

extern brain Brain;

// VEXcode devices
extern controller Controller1;

extern motor Motor_BaseLF;
extern motor Motor_BaseLM;
extern motor Motor_BaseLB;
extern motor Motor_BaseRF;
extern motor Motor_BaseRM;
extern motor Motor_BaseRB;
extern motor Motor_Roller;
extern inertial IMU;
extern smartdrive Drivetrain;
extern motor Motor_Shoot;
extern motor Motor_Lift;

void  vexcodeInit( void );