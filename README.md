<<<<<<< HEAD
# Defence-代码说明

什么都没有
=======
# Deshitted 
## Deshittors:陈佳天，黄敏达，李杰瑞，王一赫，瞿子涵



## 键位功能

- ButtonR1/2:In Take
- ButtonL1/2:Shoot
- ButtonX/Y:设置发射速度

## 各种功能函数

###  Remote_Control.cpp

1. RemoteSetUp：设置电机最大扭矩(100),设置电机角度?(0)
2. 电机驱动：

    1. RunMyVehicle：底盘控制(输入：左侧底盘电压百分比，右侧底盘电压百分比)
    2. RunMyPaw：设置爪子(输入：爪子电压百分比)
    3. RunMyShoot：设置发射(输入：发射电压百分比)
3. ShowTeamNum：显示队伍编号
4. Remote_vehicle_control：根据手柄摇杆位置等信息控制底盘
5. MyRemote：根据手柄按键等信息控制其他电机功能

###  robot-config.cpp

1. vexcodeInit：Used to initialize code/tasks/devices added using tools in VEXcode Pro.This should be called at the start of your int main function.用于使用VEXcode Pro工具添加代码/任务/设备的初始化。这应该在你的 int main 函数开始时调用。

###  MyAutoPro.cpp

###  Control_Motor.cpp

1. Control_Motors::Control_Motors：设置电机（组）配置（数量，功率单位，旋转方向，控制手柄……）
2. Control_Motors::SetUp：电机初始化设置（列表，按钮，初始角度，编码器……）
3. Control_Motors::RunMotors：通过电压，功率等使电机转动
4. Control_Motors::RemoteMotors：通过电机（组）前后方向功率控制电机
5. Control_Motors::RunMotorsRotation：转向特定角度
6. Control_Motors::StopMotors：停止所有电机
7. Control_Motors::SetStopMode：设置停止模式
8.  Control_Motors::SetTimeOut：设置电机多长时间未转到指定角度所使用的最长时间，如未完成则停止
9. Control_Motors::SetMotorsName：设置电机名称
10. Control_Motors::SetMaxTorque：设置最大扭矩
11. Control_Motors::SetMotorsRotation：设置电机角度
12. Control_Motors::GetSensorValue：获取传感器角度
13. Control_Motors::GetRpm：获取转速
14. Control_Motors::GetSpeed：获取速度
15. Control_Motors::SetMyEncoder：设置编码器
16. Control_Motors::GetEncoderValue_Deg：获取编码器角度
17. Control_Motors::CreatMotors：创建新电机（组）
18. Control_Motors::SetStopMode：设置停止模式
19. Control_Motors::GetRotationValue：获取角度
20. Debug：调试

###  main.cpp

>>>>>>> 9910aca (deshit)
