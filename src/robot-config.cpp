#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

//设置传感器
gyro MyGyro = gyro(Brain.ThreeWirePort.H);
line MyLineTracker = line(Brain.ThreeWirePort.B);

//设置手柄
controller Controller1 = controller(primary);


// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 翻译：用于使用VEXcode Pro工具添加代码/任务/设备的初始化
 * This should be called at the start of your int main function.
 * 翻译：这应该在你的 int main 函数开始时调用。
 */
void vexcodeInit(void) {
  // Nothing to initialize
  
}