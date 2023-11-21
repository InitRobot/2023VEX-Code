#pragma region VEXcode Generated Robot Configuration
#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
/*vex-vision-config:begin*/
vision::signature Vision13__BLUE_BALL = vision::signature (1, -2705, -1873, -2289,7615, 10485, 9050,2.1, 0);
vision Vision13 = vision (PORT13, 50, Vision13__BLUE_BALL);
/*vex-vision-config:end*/
#pragma endregion VEXcode Generated Robot Configuration

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

int Brain_precision = 0, Console_precision = 0, Vision13_objectIndex = 0;

float myVariable;

// "when started" hat block
int whenStarted1() {
  //printf("1");
  Brain.Screen.print("VEXcode");
  
  
  int j = 0;
  while(true){
    Vision13.takeSnapshot(Vision13__BLUE_BALL);
    j++;
    Brain.Screen.setCursor(1, 1);
    //Brain.Screen.print('1');
    //Brain.Screen.newLine();
    Brain.Screen.print("N: %d", Vision13.objectCount);
    Brain.Screen.newLine();
    for(int i = 0; i < Vision13.objectCount; i++) {
      Brain.Screen.print("X: %d", Vision13.objects[i].centerX);
      Brain.Screen.newLine();
      Brain.Screen.print("Y: %d", Vision13.objects[i].centerY);
      Brain.Screen.newLine();
    }
    Brain.Screen.print(j);
    wait(0.1, seconds);
    Brain.Screen.clearScreen();

  }
  
  return 0;
}


int main() {
  whenStarted1();
}