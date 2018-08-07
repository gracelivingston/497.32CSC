#include <stdbool.h>
#include "drvreg.h"
#define CPU_FREQ 8000000L
#define PSC_DIVISOR 1024L
#define T0_PERIOD (uint16_t)(CPU_FREQ / PSC_DIVISOR)

// Initialize Timer/Counter 0 for operation.
//
// We want:
//
// - a prescaler divisor of 1024
// - CTC mode to count up to our value
// - Don’t use the output compare
// - Enable the timer interrupt
void initTimer0() {
        TCCR0A = WGM01;
        TCCR0B = CS_PSC_1024;

        // Set the interrupt period.
        OCR0A = T0_PERIOD;
        OCR0B = 0;

        // Enable the timer interrupt.
        TIMSK0 = OCIE0A | TOIE0;

        // Reset the Counter.
        TCNT0 = 0;
}

static volatile uint8_t g_pin;

/**
 * Timer ISR for flashing LEDs.
 *
 * This is called on every timer tick. If no buttons are pressed, it
 * turns on the LED corresponding to g_pin. Otherwise, it will only
 * turn on a LED if both g_pin matches that LED and the LED’s
 * corresponding button is pressed.
 */
void __vector_23(bool switchPressed) {
        if (PINA == 0xFF) {
                PORTB = (1 << g_pin);
        } else if (!(PINA & (1 << g_pin))) {
                PORTB = (1 << g_pin);
        }

        g_pin += (g_pin + 1) % 8;
}

int main(void)
{
        // Disable interrupts while we set up.
        cli();

        // Configure port B as output
        DDRB = 0xFF;
        // Configure port A as input, and activate internal PULLUPs
        DDRA = 0x00;
        PORTA = 0xFF;

        initTimer0();

        // Enable interrupts so we can run.
        sei();

        // Loop forever
        while(true) {
                sleep();
        }
}
