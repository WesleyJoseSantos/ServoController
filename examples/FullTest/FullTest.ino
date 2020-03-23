/**
 * @file FullTest.cpp
 * @author BINARY_QUANTUM (binary-quantum.com)
 * @brief Test all features of library. Only print the output of controller.
 * @version 0.1
 * @date 2020-03-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "ServoController.h"

#define SPEED 50      //Define angular speed of controller
#define MIN_POS -90   //Define min pos of controller
#define MAX_POS 90    //Define max pos of controller
#define SIZE 7        //Define size of control arrays

ServoController controller = ServoController(SPEED, MIN_POS, MAX_POS);  //Create controller instance

//Idx of arrays is the step of servo controller. 
//If speed = 0, the value on position array will be interpreted as delat
int positions[] = {90, -90,  0, 5000, -90,  90,   0};   //Create an array of positions for controller
int speeds[]    = {50,  50, 50,    0, 180, 180, 180};   //Create an array of speeds for controller

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(controller.getStepNumber());                       //Print curret controller step (idx)
  Serial.print(" - ");                                            //Separator
  Serial.println(controller.doSteps(positions, speeds, SIZE));    //Print output of controller (doSteps method)
  if(controller.stepsDone()){                                     //Checks if steps is done
    Serial.println("Completed! Restarting...");                   //Print final message. doSteps method will go to step 0 on next loop
    delay(1000);                                                  //Wait for a second
  }
}