/* 
 * File:   
 * Author: Oscar Martinez
 * Comments:
 * Revision history: 
 */

#pragma once

#include <xc.h>


void ledInit(){
    TRISA0 = 0;
}

void ledSwitch(bool state, uint16_t time){
    PORTAbits.RA0 = state;

    DELAY_milliseconds(time);
    printf("State is %d\n", state);
}