#include <stdbool.h>
#include "drvreg.h"
#define CPU_FREQ 8000000L
#define PSC_DIVISOR 1024

void WriteReg(volatile uint8_t *RegAddr, uint8_t value) {
  *RegAddr = value;
}

uint8_t ReadReg(volatile uint8_t *RegAddr) {
  return *RegAddr;
}

// Initialize Timer/Counter 0 for operation.
//
// We want:
//
// - a prescaler divisor of 1024
// - CTC mode to count up to our value
// - Don’t use the output compare
void initTimer0() {
        TCCR0A = WGM01;
        TCCR0B = CS_PSC_1024;
}

// Use the timer to delay for some millisecs.
void timer_delay(uint16_t millisec) {
        uint8_t n = (millisec * CPU_FREQ / 1000) / PSC_DIVISOR;

        // Set the number of cycles to wait.
        WriteReg(OCR0A, n);
        WriteReg(OCR0B, 0);

        // Ensure we’ve cleared the overflow flag
        WriteReg(TOV0, OCF0A);

        // Reset the Counter.
        WriteReg(TCNT0, 0);

        // Wait for the overflow signaling a match
        while (!(ReadReg(TOV0) | OCF0A));

        // Ensure we’ve cleared the overflow flag
        WriteReg(TOV0, OCF0A);
}

void blinkLEDs(bool switchPressed) {
  // When no switch is pressed
  if( !switchPressed) {
    //  Round Robin architecture
    for(uint8_t pin = 0; pin < 8; pin++) {
      PORTB = (1 << pin);
      timer_delay(1000);
    }
  }
  else {
    for(uint8_t pin = 0; pin < 8; pin++) {
      // Check if the switch is pressed
      if(!(PINA & (1 << pin))) {
        PORTB = (1 << pin);
        timer_delay(1000);
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
