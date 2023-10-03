#include "../Inc/standardTypes.h"
#include "../Inc/common_macros.h"

//#include "../Inc/main.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"

void FPEC_voidEraseAppArea(void)
{
	uint8_t i;
	
	for (i=12;i<127;i++)
	{
		FPEC_voidFlashPageErase(i);
	}
}

void FPEC_voidFlashPageErase(uint8_t Copy_u8PageNumber)
{
	/* Wait Busy Flag */
	while (READ_BIT(FPEC->SR,0) == 1);

	/* Check if FPEC is locked or not */
	if ( READ_BIT(FPEC->CR,7) == 1)
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}
	
	/* Page Erase Operation */
	SET_BIT(FPEC->CR,1);

	/* Write Page address */
	FPEC->AR = (uint32_t)(Copy_u8PageNumber * 1024) + 0x08000000 ;

	/* Start operation */
	SET_BIT(FPEC->CR,6);

	/* Wait Busy Flag */
	while (READ_BIT(FPEC->SR,0) == 1);

	/* EOP */
	SET_BIT(FPEC->SR,5);
	CLEAR_BIT(FPEC->CR,1);
}

void FPEC_voidFlashWrite(uint32_t Copy_u32Address, uint16_t* Copy_u16Data, uint8_t Copy_u8Length)
{
	uint8_t i;
	volatile uint16_t Temp;

	while (READ_BIT(FPEC->SR,0) == 1);

	/* Check if FPEC is locked or not */
	if ( /* FPEC_CR->BitAccess.LOCK == 1 */ READ_BIT(FPEC->CR,7) == 1 )
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}
	
	
	for (i = 0; i< Copy_u8Length; i++)
	{
		/* Write Flash Programming */
		SET_BIT(FPEC->CR,0);

		/* Half word operation */

		Temp = Copy_u16Data[(uint32_t)i];
		*((volatile uint16_t*)Copy_u32Address) = Copy_u16Data[(uint32_t)i];
		Copy_u32Address += 2 ;

		/* Wait Busy Flag */
		while (READ_BIT(FPEC->SR,0) == 1);
	
		/* EOP */
		SET_BIT(FPEC->SR,5);
		CLEAR_BIT(FPEC->CR,0);
	}

}
