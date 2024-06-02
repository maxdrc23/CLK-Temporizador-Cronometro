
/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "dipswitch.h"
#include "gpio4Displays.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DELAY		0x3000
#define DELAY_CLK	0xFFFA

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */

int main(void)
{
	volatile uint32_t wDelay = DELAY;
	volatile uint32_t wDelayClk = DELAY_CLK;

	vfnInitGpios();

    while (1)
    {
    	if(!wDelay--)
    	{
    		vfnColumns_Driver();
    		//vfnDisplay_Value();
    		wDelay = DELAY;
    	}
    	if(!wDelayClk--)
    	{
    		//vfnDisplay_Value();
    		vfnClk();
			wDelayClk = DELAY_CLK;
    	}
    }
}
