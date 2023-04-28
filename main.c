#include "mcc_generated_files/mcc.h"
#include "LedControl.h"

#define PIN_READ   0
#define PIN_WRITE  2

#define DELAY_PERIOD 500

#define MESSAGE_ID 0x123


void main(void){
    SYSTEM_Initialize();
    //INTERRUPT_GlobalInterruptEnable();
    //INTERRUPT_GlobalInterruptDisable();
    //INTERRUPT_PeripheralInterruptEnable();
    //INTERRUPT_PeripheralInterruptDisable();
    portsInit();
    uCAN_MSG msg;
    msg.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
    msg.frame.id = MESSAGE_ID;
    msg.frame.dlc = 1;
    msg.frame.data0 = 0x00;
    while (true){
      CAN_transmit(&msg);
      msg.frame.data0++;
      portAPinWrite(PIN_WRITE, true);
      DELAY_milliseconds(DELAY_PERIOD);
      portAPinWrite(PIN_WRITE, false);
      DELAY_milliseconds(DELAY_PERIOD);
    }
    return;
}