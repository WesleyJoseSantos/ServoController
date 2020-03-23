/**
 * @file ServoController.h
 * @author BINARY_QUANTUM (binary-quantum.com)
 * @brief Library for general servo control. Work's with any generic servo library.
 * @version 0.1
 * @date 2020-03-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _ServoController_H
#define _ServoController_H

#include <Arduino.h>

class ServoController
{
private:
    unsigned long _spd;
    int _min, _max, _pos, _idx;
    unsigned long auxMillis, auxMillisDelay;
    bool _done, _stepsDone;
    bool onLimit();
    bool timer();
    bool timerDelay(unsigned long val);
public:
    ServoController(int spd, int min, int max);
    void setSpd(int spd);
    void setMin(int min);
    void setMax(int max);
    int getPos();
    int moveTo(int pos);
    int doSteps(int *steps, int stepsSize);
    int doSteps(int *steps, int *speeds, int stepsSize);
    int getStepNumber();
    bool stepsDone();
};

#endif //_ServoController_H
