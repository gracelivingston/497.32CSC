#include "drvreg.h"
#define CPU_FREQ 8000000L

void WriteReg(volatile uint8_t *RegAddr, uint8_t value) {
  *RegAddr = value;
}

uint8_t ReadReg(volatile uint8_t *RegAddr) {
  return *RegAddr;
}

void soft_delay(volatile uint16_t millisec) {
  // CPU running at CPU_FREQ i.e CPU_FREQ instructions per seconds
  // Or 8000 instructions per milliseconds
  for(volatile uint16_t count = 0; count < (millisec * 8000); count++) {
    ;
  }
}

int main(void)
{
  // Configure port A as output
  WriteReg(DDRA, 0xFF);

  // Loop forever
  while(1) {
    // Turn ON LEDs on port A
    WriteReg(PORTA, 0xFF);
    soft_delay(1000);
    // Turn OFF LEDs on port A
    WriteReg(PORTA, 0x00);
    soft_delay(1000);
  }
}
