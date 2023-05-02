/* 
 * File:   
 * Author: Oscar Martinez
 * Comments:
 * Revision history: 
 */

#pragma once

#include <xc.h>


void portsInit(){
    // initialize the GPIO A as an output
    TRISA = 0x00;
    //initialize the GPIO B as an input
    TRISB = 0xCB;

}

void portAPinWrite(uint8_t pin, bool state){
    PORTA = (state << pin);
}

void portBPinWrite(uint8_t pin, bool state){
    PORTB = (state << pin);
}

bool portBPinRead(uint8_t pin){
    return PORTB & (1 << pin);
}

bool portCPinRead(uint8_t pin){
    return PORTC & (1 << pin);
}

void portAPinWrite_ms(uint8_t pin, bool state, uint16_t time){
    portAPinWrite(pin, state);
    DELAY_milliseconds(time);
    printf("State is %d\n", state);
}

void bridgePortAPinToPortBPin(uint8_t pinRead, uint8_t pinWrite){
    bool state = portBPinRead(pinRead);
    portAPinWrite(pinWrite, state);
}