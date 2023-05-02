#include "mcc_generated_files/mcc.h"
#include "DevicesFunctions.h"
#include "AnalogTrigger.h"


#define STBY_CAN_PIN 1
#define LED_PIN  2

#define LDR_PIN 0x0A
#define TRIGGER_ID 0x42
#define LDR_THRESHOLD 0xD000
#define GUARD_CYCLES 10000

#define MESSAGE_ID 0x69

#define DELAY_PERIOD 500

void actOnTriggerCallback(uint8_t triggerID, bool state){
  uCAN_MSG msgTX;
  msgTX.frame.id = MESSAGE_ID;
  msgTX.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
  msgTX.frame.dlc = 0x02;
  msgTX.frame.data0 = triggerID;
  msgTX.frame.data1 = state;
  CAN_transmit(&msgTX);
  portAPinWrite(LED_PIN, state);
  DELAY_milliseconds(DELAY_PERIOD);
}

void main(void){
  SYSTEM_Initialize();
  INTERRUPT_GlobalInterruptEnable();
  INTERRUPT_PeripheralInterruptEnable();
  portBPinWrite(STBY_CAN_PIN, false);
  initTrigger(TRIGGER_ID, LDR_PIN, LDR_THRESHOLD, GUARD_CYCLES);
  
  while (true){
    readnShoot(actOnTriggerCallback);
  }
}