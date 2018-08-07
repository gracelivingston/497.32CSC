#include <stdbool.h>
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
  // Or CPU_FREQ/1000 instructions per milliseconds
  for(volatile uint16_t count = 0; count < (millisec * CPU_FREQ / 1000); count++) {
    ;
  }
}

void blinkLEDs(bool switchPressed) {
  // When no switch is pressed
  if( !switchPressed) {
    //  Round Robin architecture
    for(uint8_t pin = 0; pin < 8; pin++) {
      PORTB = (1 << pin);
      soft_delay(1000);
    }
  }
  else {
    for(uint8_t pin = 0; pin < 8; pin++) {
      // Check if the switch is pressed
      if(!(PINA & (1 << pin))) {
        PORTB = (1 << pin);
        soft_delay(1000);
      }
    }
  }
}

int main(void)
{
  // Configure port B as output
  DDRB = 0xFF;
  // Configure port A as input, and activate internal PULLUPs
  DDRA = 0x00;
  PORTA = 0xFF;

  // Loop forever
  while(true) {
    // When no switch is pressed
    if(PINA == 0xFF) {
      blinkLEDs(false);
    }
    else {
      blinkLEDs(true);
    }
  }
}
