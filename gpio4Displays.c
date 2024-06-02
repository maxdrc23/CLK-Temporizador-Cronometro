/*
 * gpio_matriz8x8.h
 *
 *  Created on: Jan 27, 2024
 *      Author: Mario Castaneda
 */
/******************************************************************************/
/***        Include files                                                   ***/
/******************************************************************************/
#include <gpio4Displays.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SEGMENT_A		(0)
#define SEGMENT_B		(1)
#define SEGMENT_C		(2)
#define SEGMENT_D		(3)
#define SEGMENT_E		(4)
#define SEGMENT_F		(5)
#define SEGMENT_G		(6)
#define SEGMENT_DEC		(9)

#define D1_PIN	(8)
#define D2_PIN	(10)
#define D3_PIN	(20)
#define D4_PIN	(21)


#define SEGA 	(1<<SEGMENT_A)
#define SEGB 	(1<<SEGMENT_B)
#define SEGC 	(1<<SEGMENT_C)
#define SEGD 	(1<<SEGMENT_D)
#define SEGE 	(1<<SEGMENT_E)
#define SEGF 	(1<<SEGMENT_F)
#define SEGG 	(1<<SEGMENT_G)
#define SEGDEC	(1<<SEGMENT_DEC)

#define SEVEN_SEGS_ZERO		(SEGA | SEGB | SEGC | SEGD | SEGE | SEGF)
#define SEVEN_SEGS_ONE		(SEGB | SEGC)
#define	SEVEN_SEGS_TWO		(SEGA | SEGB | SEGD | SEGE | SEGG)
#define	SEVEN_SEGS_THREE	(SEGA | SEGB | SEGC | SEGD | SEGG)
#define	SEVEN_SEGS_FOUR		(SEGB | SEGC | SEGF | SEGG)
#define	SEVEN_SEGS_FIVE		(SEGA | SEGC | SEGD | SEGF | SEGG)
#define	SEVEN_SEGS_SIX		(SEGA | SEGC | SEGD | SEGE | SEGF | SEGG)
#define	SEVEN_SEGS_SEVEN	(SEGA | SEGB | SEGC | SEGG)
#define	SEVEN_SEGS_EIGHT	(SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG)
#define	SEVEN_SEGS_NINE		(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG)

#define SEVEN_SEGS_ZERO_S	SEVEN_SEGS_ZERO | SEGDEC
#define SEVEN_SEGS_ONE_S	SEVEN_SEGS_ONE | SEGDEC
#define SEVEN_SEGS_TWO_S	SEVEN_SEGS_TWO | SEGDEC
#define SEVEN_SEGS_THREE_S	SEVEN_SEGS_THREE | SEGDEC
#define SEVEN_SEGS_FOUR_S	SEVEN_SEGS_FOUR | SEGDEC
#define SEVEN_SEGS_FIVE_S	SEVEN_SEGS_FIVE | SEGDEC
#define SEVEN_SEGS_SIX_S	SEVEN_SEGS_SIX | SEGDEC
#define SEVEN_SEGS_SEVEN_S	SEVEN_SEGS_SEVEN | SEGDEC
#define SEVEN_SEGS_EIGHT_S	SEVEN_SEGS_EIGHT | SEGDEC
#define SEVEN_SEGS_NINE_S	SEVEN_SEGS_NINE | SEGDEC
/*******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Local Variables
 ******************************************************************************/
static GPIO_Type *rgGpio1 = GPIO;
static const uint32_t bDisplayDriver[] =
{
	DISPLAY1,
	DISPLAY2,
	DISPLAY3,
	DISPLAY4,
};

#define TOTAL_DISPLAYS	(sizeof(bDisplayDriver)/sizeof(bDisplayDriver[0]))


static const uint16_t bBCD7Segs[] =
{
	SEVEN_SEGS_ZERO,	// 0
	SEVEN_SEGS_ONE,		// 1
	SEVEN_SEGS_TWO,		// 2
	SEVEN_SEGS_THREE,	// 3
	SEVEN_SEGS_FOUR,	// 4
	SEVEN_SEGS_FIVE,	// 5
	SEVEN_SEGS_SIX,		// 6
	SEVEN_SEGS_SEVEN,	// 7
	SEVEN_SEGS_EIGHT,	// 8
	SEVEN_SEGS_NINE,	// 9
	SEVEN_SEGS_ZERO_S, 	//0.
	SEVEN_SEGS_ONE_S, 	//1.
	SEVEN_SEGS_TWO_S,	//2.
	SEVEN_SEGS_THREE_S,	//3.
	SEVEN_SEGS_FOUR_S,	//4.
	SEVEN_SEGS_FIVE_S,	//5.
	SEVEN_SEGS_SIX_S,	//6.
	SEVEN_SEGS_SEVEN_S,	//7.
	SEVEN_SEGS_EIGHT_S,	//8.
	SEVEN_SEGS_NINE_S	//9.
};

static uint8_t bDisplayIdx = 0;
uint8_t gbaDisplayData[TOTAL_DISPLAYS] = {0};

/*******************************************************************************
* Code
******************************************************************************/

/*******************************************************************************
 * vfnInitRGB
 * DESCRIPTION:Init The PORT 1 for the OKDO RGB Led
 * RETURNS:
 * void
 ******************************************************************************/
void vfnInitGpios()
{
	/*Init SYSCOM IOCON clock*/
	SYSCON_Type *rSyscon = SYSCON;
	IOCON_Type *rPinSetup = IOCON;

	/*Enable IOCON clock*/
	rSyscon->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_IOCON_MASK;

	/*Enable GPIO1 or PORT 1 Clock*/
	rSyscon->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_PRESETCTRL0_GPIO1_RST_MASK | SYSCON_PRESETCTRL0_GPIO0_RST_MASK;

	/*Set Up Pin 15.5.1 Type D IOCON registers*/
	rPinSetup->PIO[PORT1_LED][SEGMENT_A] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1_LED][SEGMENT_B] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1_LED][SEGMENT_C] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1_LED][SEGMENT_D] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1_LED][SEGMENT_E] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1_LED][SEGMENT_F] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1_LED][SEGMENT_G] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1_LED][SEGMENT_DEC] |= IOCON_PIO_FUNC(0);

	rPinSetup->PIO[PORT1_LED][D1_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1_LED][D2_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1_LED][D3_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1_LED][D4_PIN] |= IOCON_PIO_FUNC(0);

	/*16.5.3 GPIO port direction registers*/
	rgGpio1->DIR[PORT1_LED] |= ALL_PORT1 | DISPLAY1 | DISPLAY2 | DISPLAY3 | DISPLAY4;
	/*Turn off all leds*/
	rgGpio1->CLR[PORT1_LED] |= ALL_PORT1 | DISPLAY1 | DISPLAY2 | DISPLAY3 | DISPLAY4;
}
/*******************************************************************************
 * vfnTurnOff
 * DESCRIPTION: Power Off RGB Leds
 * RETURNS:
 * void
 ******************************************************************************/
void vfnColumns_Driver()
{
	/*Columns and Lines Turn off*/
	rgGpio1->CLR[PORT1_LED] |= ALL_PORT1;
	rgGpio1->SET[PORT1_LED] |= DISPLAY1 | DISPLAY2 | DISPLAY3 | DISPLAY4;

	rgGpio1->SET[1] = (bBCD7Segs[gbaDisplayData[bDisplayIdx]]); // Current Display Data
	rgGpio1->CLR[PORT1_LED] = (bDisplayDriver[bDisplayIdx]);	//Turn on Current Column;
	if ( ++bDisplayIdx > TOTAL_DISPLAYS)
	{
		bDisplayIdx = 0;
	}
}
//------------------------------------------------------------------------------
/*!
    \fn		vfnDisplay_Value
    \param	none
    \return	none
    \brief	Assign value
*/
void vfnDisplay_Value(uint8_t bHra_d, uint8_t bHra_u, uint8_t bMin_d, uint8_t bMin_u)
{
	gbaDisplayData[0] = bHra_d;
	gbaDisplayData[1] = bHra_u;
	gbaDisplayData[2] = bMin_d;
	gbaDisplayData[3] = bMin_u;
}

void vfnClk()
{
	static uint8_t bHra = 0;
	static uint8_t bMin = 0;
	static uint8_t bSeg = 0;
	static uint8_t bHlfSeg = 0;

	bHlfSeg++;

	if(bHlfSeg == 2)
	{
		bHlfSeg = 0;
		bSeg++;
	}

	if(bSeg == 60)
	{
		bSeg = 0;
		bMin++;
	}

	if(bMin==60)
	{
		bMin = 0;
		bHra++;
	}

	if(bHra==24)
	{
		bHra=0;
	}

	if(bHlfSeg==1)
	{
		vfnDisplay_Value((bHra/10),(bHra%10), (bMin/10), (bMin%10));
	}
	else
	{
		vfnDisplay_Value((bHra/10),(bHra%10), (bMin/10), (bMin%10)+10);
	}
}
