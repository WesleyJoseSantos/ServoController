/**
 * @file ServoSweep.cpp
 * @author BINARY_QUANTUM (binary-quantum.com)
 * @brief Demonstrate the use of controller with Servo.h lib
 * @version 0.1
 * @date 2020-03-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <Servo.h>
#include "ServoController.h"

#define SERVO_PIN 9     //Define servo pin
#define SPEED 10        //Define angular speed of controller
#define MIN_POS 0       //Define min pos of controller
#define MAX_POS 180     //Define max pos of controller
#define START 0         //Define start position
#define SIZE 2          //Define size of control arrays

ServoController controller(SPEED, MIN_POS, MAX_POS);    //Create servo controller
Servo servo;                                            //Create servo

int positions[] = {180, 0};     //Control array with servo positions

void setup(){
    servo.attach(9);        // attaches the servo on pin 9 to the servo object
    servo.write(START);     // go to start position
}

void loop(){
    servo.write(controller.doSteps(positions, SIZE));     //Write on servo the output of controller using doSteos method
}