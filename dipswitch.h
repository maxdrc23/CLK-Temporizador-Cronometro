/*
 * dipswitch.h
 *
 *  Created on: Jan 25, 2024
 *      Author: Mario Castaneda
 */

#ifndef DIPSWITCH_H_
#define DIPSWITCH_H_
/******************************************************************************/
/***        Include files                                                   ***/
/******************************************************************************/
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SWITCH_PORT 1
#define SWITCH0     13
#define SWITCH1		14
#define SWITCH2		15
#define SWITCH3		16
/*******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/
void vfnInitDipSwitch();
uint8_t bfnSwitch();
/*******************************************************************************
 * Local Variables
 ******************************************************************************/

 /******************************************************************************
 * Extern Variables Section
 ******************************************************************************/

 /******************************************************************************
 * Extern Constants Section
 ******************************************************************************/

/*******************************************************************************
 * Function Prototypes Section
 ******************************************************************************/

/******************************************************************************/

/*******************************************************************************
 * End of File
 ******************************************************************************/
#endif /* DIPSWITCH_H_ */
