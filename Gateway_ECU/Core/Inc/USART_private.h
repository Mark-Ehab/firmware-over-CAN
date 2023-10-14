
#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

typedef struct{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR[3];
	volatile uint32_t GTPR;
}USART_Register;


#define 	USART1_ 		((USART_Register *) 0x40013800)

#endif
