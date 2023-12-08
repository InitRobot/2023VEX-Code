# 2023VEX-16076B

## ***Source: [VEX V5 Program Template](https://github.com/CreatechStudio/VEX-V5-Program-Template)***

## 接线（以主控为原点，滚筒为前方）

1. 左前电机
2. 左后上方电机
3. 左后下方电机
4. 右前电机
5. 右后上方电机
6. 无
7. 无
8. 无线接收器
9. 右后下方电机
10. IMU ***（经费不足目前没有）***
11. 发射
12. 滚筒小电机
13. 无
14. 无
15. 爬升触发

## 自动

自动在***include\parameters.h*第六行调节**，对应关系如下

### auton_strategy = 0

屏幕显示 auto one

### auton_strategy = 1

屏幕显示 auto two

### auton_strategy = 2

屏幕显示 auto three

### auton_strategy = 3

屏幕显示 auto four

### auton_strategy = 4

什么都不做，屏幕显示yousb

## 操作

### 摇杆

- axis1：前后
- axis2：转向

### 按钮

- 上：滚筒向外吐球
- 下：滚筒向内吸球
- 左：滚筒停

## 模板简介

​这是一个基于VEX V5竞赛模板的基本程序，它由C++编写，包含了

- 基本的底盘控制
- PID控制
- PID调参
- 基于电机编码器与陀螺仪的GPS定位
- 自动框架
