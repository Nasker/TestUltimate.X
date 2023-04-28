#include "mcc_generated_files/mcc.h"
#include "LedControl.h"

#define PIN_READ   0
#define PIN_WRITE  2
#define STBY_CAN_PIN 1

#define DELAY_PERIOD 1000

#define MESSAGE_ID 0x69


void main(void){
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    uCAN_MSG msgTX;
    uCAN_MSG msgRX;
    msgTX.frame.id = MESSAGE_ID;
    msgTX.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
    msgTX.frame.dlc = 0x01;
    msgTX.frame.data0 = 0xFE;
    CAN_transmit(&msgTX);
    portBPinWrite(STBY_CAN_PIN, false);
    while (true){
      if(CAN_receive(&msgRX)){
        msgRX.frame.data0 *= 2;
        msgRX.frame.data1 /= 2;
        msgRX.frame.data2 += 2;
        msgRX.frame.data3 -= 2;
        CAN_transmit(&msgRX);
      }
      CAN_transmit(&msgTX);
      msgTX.frame.data0++;
      DELAY_milliseconds(DELAY_PERIOD);
    }
    return;
}