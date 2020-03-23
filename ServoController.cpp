/**
 * @file ServoController.cpp
 * @author BINARY_QUANTUM (binary-quantum.com)
 * @brief Library for general servo control. Work's with any generic servo library.
 * @version 0.1
 * @date 2020-03-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "ServoController.h"

/**
 * @brief Construct a new Servo Controller:: Servo Controller object
 * 
 * @param spd angular speed of servo
 * @param min min angle limit
 * @param max max angle limit
 */
ServoController::ServoController(int spd, int min, int max){
    _spd = spd;
    _min = min;
    _max = max;
    _done = false;
    _stepsDone = false; 
    auxMillis = 0;
    auxMillisDelay = 0;
}

/**
 * @brief Set angular speed
 * 
 * @param spd new angular speed
 */
void ServoController::setSpd(int spd){
    _spd = spd;
}

/**
 * @brief set min angle limit
 * 
 * @param min new limit
 */
void ServoController::setMin(int min){
    _min = min;
}

/**
 * @brief set max angle limit
 * 
 * @param max new limit
 */
void ServoController::setMax(int max){
    _max = max;
}

/**
 * @brief get current position of servo controller
 * 
 * @return int current position
 */
int ServoController::getPos(){
    return(_pos);
}

/**
 * @brief move servo with pre-defined angular speed
 * 
 * @param pos pos to be reached
 * @return int output of controller
 */
int ServoController::moveTo(int pos){
    _done = pos == _pos;
    if(timer() && !_done) _pos = _pos < pos ? _pos+1 : _pos-1;
    if(onLimit()) return(pos);
    return(_pos);
}

/**
 * @brief controls servo using an array of positions
 * 
 * @param positions array of positions
 * @param stepsSize size of array
 * @return int output of controller
 */
int ServoController::doSteps(int *positions, int stepsSize){
    moveTo(positions[_idx]);
    if(_pos == positions[_idx]) _idx++;
    _stepsDone = _idx == stepsSize;
    if(_stepsDone) _idx = 0;
    return(_pos);
}

/**
 * @brief controls servo using an array of positions/speeds
 * 
 * @param steps array of positions or time delay if speed = 0
 * @param speeds array of speeds
 * @param stepsSize size of arrays
 * @return int output of controller
 */
int ServoController::doSteps(int *positions, int *speeds, int stepsSize){
    if(speeds[_idx] != 0){
        setSpd(speeds[_idx]);
        return(doSteps(positions, stepsSize));
    }else{
        if(timerDelay(positions[_idx])) _idx++;
        return(_pos);
    }
}

/**
 * @brief get current step of doSteps controller
 * 
 * @return int current step of doSteps controller
 */
int ServoController::getStepNumber(){
    return(_idx);
}

/**
 * @brief checks if doStep controller is done
 * 
 * @return true if steps is done
 * @return false if not
 */
bool ServoController::stepsDone(){
    return(_stepsDone);
}

/**
 * @brief checks if the controller has reached the position limits
 * 
 * @return true if position has reached an limit
 * @return false if not
 */
bool ServoController::onLimit(){
    return(_pos >= _max || _pos <= _min);
}

/**
 * @brief Auxiliar timer for servo movement controller
 * 
 * @return true on interval end tick
 * @return false while timer is running
 */
bool ServoController::timer(){
    if(!auxMillis) auxMillis = millis();
    bool ret = millis() - auxMillis > (1000/_spd);
    if(ret) auxMillis = 0;
    return(ret);
}

/**
 * @brief Timer delay controller
 * 
 * @param val interval of timer
 * @return true on interval end tick
 * @return false while timer is running
 */
bool ServoController::timerDelay(unsigned long val){
    if(!auxMillisDelay) auxMillisDelay = millis();
    bool ret = millis() - auxMillisDelay >= val;
    if(ret) auxMillisDelay = 0;
    return(ret);
}