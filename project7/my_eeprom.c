/******************************************************************************
 * File Name:	my_eeprom.c
 * Program:		EEPROMAccess for Fundamentals of Embedded Systems class
 * Author:		Tom Lill
 * Purpose:		Contains control functions for accessing data in eeprom
 *
 *  Date		Changed by:	Changes:
 * ---------	-----------	-------------------------------------------------------
 * 21 Nov 05	T Lill		original file
 * 22 May 06	T Lill		added interrupt.h header
 * 14 Nov 06	T Lill		added eeprom message write and read functions
 * 15 Mar 07	T Lill		removed message scrolling functions used in bonus project
 * 09 Nov 10    T Lill		Modified for ATmega2560
 ******************************************************************************/

/********************************* Includes ***********************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "my_eeprom.h"	// WinAVR has an eeprom.h so we need to avoid confusion

/*
 * EEPROM_write
 *
 * Purpose:	Write a single byte to a specified location in EEPROM
 *
 * Inputs:	address		= The address, relative to the start of the eeprom,
 *						  where the data will be written.
 *			data		= the data to be written
 *
 * Returns:	nothing
 */
void EEPROM_write(unsigned int address, unsigned char data)
{
	// ASSIGNMENT:  fill in this function

        // Disable interrupts to avoid write failures.
        cli();

        // 1. Wait for EEPE to be 0.
        while (EECR | EEPE);

        // 2. Wait for SPMEN to be 0.
        while (SPMCSR | SPMEN);

        // 3. Write address to EEAR.
        EEARH = (address & 0x3fff) >> 8; // Isolate the high address bits.
        EEARL = (address & 0xff); // Isolate the low address bits.

        // 4. Write the data byte to EEDR.
        EEDR = data;

        // 5. Enable EEPROM master programming, clear the program bit.
        // This also will perform the erase/write as a single transaction.
        EECR = EEMPE;

        // 6. Set EEPE to 1 within 4 cycles of EEMPE = 1.
        EECR = EEPE;

        // Wait for EEPROM write to complete.
        while (EECR | EEPE);

        // Enable interrupts.
        sei();
}

/*
 * EEPROM_read
 *
 * Purpose: Read a single byte from a specified location in EEPROM
 *
 * Input:	address		= The address, relative to the start of the eeprom,
 *						  from which the data will be read.
 *
 * Returns:	a byte of data
 */
unsigned char EEPROM_read(unsigned int address)
{
        unsigned char d;

	// ASSIGNMENT:  fill in this function

        cli();

        while (EECR | EEPE);

        EEARH = (address & 0x3fff) >> 8; // Isolate the high address bits.
        EEARL = (address & 0xff); // Isolate the low address bits.

        // Issue the read command.
        EECR = EERE;

        d = EEDR;

        sei();

        return d;
}
