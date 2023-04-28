#include "mcc_generated_files/mcc.h"
#include "LedControl.h"


#define STBY_CAN_PIN 1
#define LED_PIN  2
#define LDR_PIN 0x0A

#define MESSAGE_ID 0x69

#define LDR_THRESHOLD 0xD000

#define DELAY_PERIOD 50

void main(void){
  SYSTEM_Initialize();
  INTERRUPT_GlobalInterruptEnable();
  INTERRUPT_PeripheralInterruptEnable();
  uCAN_MSG msgTX;
  uCAN_MSG msgRX;
  msgTX.frame.id = MESSAGE_ID;
  msgTX.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
  msgTX.frame.dlc = 0x02;
  portBPinWrite(STBY_CAN_PIN, false);
  while (true){
    ADC_StartConversion(LDR_PIN);
    uint16_t convertedValue = ADC_GetConversionResult();

    msgTX.frame.data0 = convertedValue >> 8;
    msgTX.frame.data1 = convertedValue & 0xFF;
    CAN_transmit(&msgTX);

    portAPinWrite(LED_PIN, convertedValue < LDR_THRESHOLD);

    DELAY_milliseconds(DELAY_PERIOD);
  }
}