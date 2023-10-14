
#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

/* Defining Macros */

#define USART_U8_8_BIT_WORD					0
#define USART_U8_9_BIT_WORD					1

#define USART_U8_PARITY_DISABLED			0
#define USART_U8_PARITY_ENABLED				1

#define USART_U8_EVEN_PARITY				0
#define USART_U8_ODD_PARITY					1

#define USART_U8_PE_DISABLED				0
#define USART_U8_PE_ENABLED					1


/*******************/

void MUSART1_voidInit(void);

void MUSART1_voidTransmit(uint8_t arr);

uint8_t MUSART1_u8Receive(uint8_t* Copy_u8Data);

#endif






