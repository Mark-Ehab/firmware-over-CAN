
#include "../Inc/standardTypes.h"
#include "../Inc/common_macros.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"


void MUSART1_voidInit(void)
{
	/*	baud rate = 9600		*/
	USART1_ -> BRR = 0x341;

	SET_BIT((USART1_-> CR[0]), 3);			/* Enabling Transmitter */
	SET_BIT((USART1_-> CR[0]), 2);			/* Enabling Receiver */
	SET_BIT((USART1_-> CR[0]), 13);			/* Enabling USART */

	USART1_ -> SR = 0;						/* Clearing status register */
}

void MUSART1_voidTransmit(uint8_t arr)
{
	uint8_t i = 0;
	//	while(arr[i] != '\0'){
	USART1_ -> DR = arr;
	while((GET_BIT((USART1_ -> SR), 6)) == 0);
	i++;
	//	}

}

uint8_t MUSART1_u8Receive(uint8_t* Copy_u8Data)
{
	uint8_t Local_u8Result = 1;

	if ( (GET_BIT((USART1_ -> SR), 5)) == 1 )
	{
		*Copy_u8Data = USART1_ -> DR;
	}
	else
	{
		Local_u8Result = 0;
	}

	return (Local_u8Result);
}




















