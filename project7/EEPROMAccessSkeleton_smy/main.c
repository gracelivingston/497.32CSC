/******************************************************************************
 * File Name:	Main.c
*/



#include "lib.c"
#include "menu.c"
#include "lcd.c"
#include "interrpt.c"
#include "heartbeat.h"
#include "serial.h"
#include "errors.c"
#include "serial.c"
#include "my_eeprom.c"


/************************* Function Prototypes ******************************/
int main(void);

/*********************** Function Implementations ******************************/

/*
 * Since all we really want to do is toggle an LED on and off, there's no
 * point in keeping track of its state.  Just initialize the heartbeat LED,
 * then write 1 to PINB which toggles the bit.
 */
void heartbeat(void)
{
	asm volatile (" sbi	0x09, 0 ");	// see warning in lib.h about SET_BIT
}

/*****************************************************************************
 * Main function.
 *
 * Initializes hardware and software. Then enters the endless foreground loop.
 *
 *****************************************************************************/
int main(void)
{
	// Disable interrupts
	cli();

	// Set port D as an output and turn off all LEDs
	DDRD = 0xFF;
	PORTD = 0xFF;

	/* Initialize the Timer 0 */
	ISR_InitTimer0();

	// Initialize serial I/O
	SCIInitialize();

	/*
	 * Enable interrupts. Do as last initialization, so interrupts are
	 * not initiated until all of initialization is complete.
	 */
	sei();

	for ( ; ;)		/* Foreground loops forever */
	{
		// Do slow tasks here
	}   /* end of endless loop */

	return 0;
}
