/*
 * dipswitch.c
 *
 *  Created on: Jan 25, 2024
 *      Author: Mario Castaneda
 */
#include "dipswitch.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Local Variables
 ******************************************************************************/
static GPIO_Type *rgGpio1 = GPIO;
/*******************************************************************************
* Code
*******************************************************************************/
/*******************************************************************************
 * vfnInitDipSwitch
 * DESCRIPTION:Init The PORT 1 for the OKDO Input Por Pins 0 and 1
 * RETURNS:
 * void
 ******************************************************************************/
void vfnInitDipSwitch()
{
	SYSCON_Type *rClocks = SYSCON;
	IOCON_Type *rPinSetup = IOCON;

	/*Init Clocks IOCON 4.5.17 AHB clock control 0*/
	rClocks->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_IOCON_MASK | SYSCON_AHBCLKCTRL0_GPIO0_MASK;

	/*Set Up Pin 15.5.1 Type D IOCON registers*/
	rPinSetup->PIO[SWITCH_PORT][SWITCH0] |= IOCON_PIO_FUNC(0) | IOCON_PIO_MODE(1) | IOCON_PIO_DIGIMODE_MASK;
	rPinSetup->PIO[SWITCH_PORT][SWITCH1] |= IOCON_PIO_FUNC(0) | IOCON_PIO_MODE(1) | IOCON_PIO_DIGIMODE_MASK;
	rPinSetup->PIO[SWITCH_PORT][SWITCH2] |= IOCON_PIO_FUNC(0) | IOCON_PIO_MODE(1) | IOCON_PIO_DIGIMODE_MASK;
	rPinSetup->PIO[SWITCH_PORT][SWITCH3] |= IOCON_PIO_FUNC(0) | IOCON_PIO_MODE(1) | IOCON_PIO_DIGIMODE_MASK;

	/*GPIO as output 16.5.3 GPIO port direction registers*/
	rgGpio1->DIR[SWITCH_PORT] &= ~(( 1<<SWITCH0 ) | ( 1<<SWITCH1 ) | (1<<SWITCH2) | (1<<SWITCH3));
}
/*******************************************************************************
 * bfnSwitch
 * DESCRIPTION: Read out and make a & mask for the PIO0 and PIO1
 * RETURNS:
 * uint8_t GPIO Input value
*******************************************************************************/
uint8_t bfnSwitch()
{
	uint8_t bValue;

	/*16.5.5 GPIO port pin registers*/
	/* 0 = Read: pin is low, write: clear output bit.
	 * 1 = Read: pin is high, write: set output bit.*/

	/* 8 bits = binary 0001 0111 &
	 * 				   0000 0011
	 * 				   0000 0010
	 * */

	bValue = ( rgGpio1->PIN[SWITCH_PORT] & (( 1<<SWITCH0 ) | ( 1<<SWITCH1 )));

	return bValue;
}
