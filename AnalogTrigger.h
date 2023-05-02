#pragma once

#include <xc.h>
#include "mcc_generated_files/adc.h"


uint8_t _ID = 0;
uint8_t _inputPin = 0;
uint16_t _reading = 0;
bool _state = false;
bool _prevState = false;
uint16_t _threshold = 0;
bool _shootGuard = false;
uint16_t _countGuardCycles = 10000;  
uint16_t _countGuard = 0;  
	

void setID(uint8_t ID){
    _ID = ID;
}

void setCountGuard(uint16_t count){
    _countGuardCycles = count;
}

bool overThreshold(){
    return _state;
}

void setAnalogChannel(uint8_t channel){
    _inputPin = channel;
}

void setThreshold(uint16_t value){
    _threshold = value;
}

void initTrigger(uint8_t ID, uint8_t channel, uint16_t threshold, uint16_t countGuardCycles){
    setID(ID);
    setAnalogChannel(channel);
    setThreshold(threshold);
    setCountGuard(countGuardCycles);
    _prevState = false;
    _shootGuard = false;
    _countGuard = 0;
    _state = false;
}

void readnShoot(void (*userFunction)(uint8_t, bool)){
    ADC_StartConversion(_inputPin);
    _reading = ADC_GetConversion(_inputPin);
    if(_shootGuard) 
        _countGuard++;

    if(_countGuard >= _countGuardCycles){
        _shootGuard=false;
        _countGuard=0;
    }
    
    if(_reading > _threshold){
        _state = true;  
        }
        else{
        _state = false;
    }
    if(_state != _prevState){
        if((_state)&&(!_shootGuard)){
        (*userFunction)(_ID,true);
        _shootGuard=true;
        _countGuard=0; 
        }
        if(!_state){
        (*userFunction)(_ID,false);
        }
        _prevState = _state;
    }
}   