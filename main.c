#include "mcc_generated_files/mcc.h"
#include "LedControl.h"


void main(void){
    SYSTEM_Initialize();
    //INTERRUPT_GlobalInterruptEnable();
    //INTERRUPT_GlobalInterruptDisable();
    //INTERRUPT_PeripheralInterruptEnable();
    //INTERRUPT_PeripheralInterruptDisable();
    ledInit();
    while (true){
        ledSwitch(true, 250);
        ledSwitch(false, 250);
    }
    return;
}
/**
 End of File
*/