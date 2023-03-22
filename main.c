#include "mcc_generated_files/mcc.h"
#include "LedControl.h"

#define PIN_READ   0
#define PIN_WRITE  2

#define DELAY_PERIOD 250


void main(void){
    SYSTEM_Initialize();
    //INTERRUPT_GlobalInterruptEnable();
    //INTERRUPT_GlobalInterruptDisable();
    //INTERRUPT_PeripheralInterruptEnable();
    //INTERRUPT_PeripheralInterruptDisable();
    portsInit();
    while (true){
      if(portBPinRead(PIN_READ)){
        portAPinWrite_ms(PIN_WRITE, true, DELAY_PERIOD);
        portAPinWrite_ms(PIN_WRITE, false, DELAY_PERIOD);
      }
    }
    return;
}