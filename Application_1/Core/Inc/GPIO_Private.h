/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 7, 2023               	*/
/*      			SWC          : GPIO  			            */
/*     			    Description	 : GPIO Private                 */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*		                      _____ _____ _____ ____    _____      _            _                           */
/*		                     / ____|  __ \_   _/ __ \  |  __ \    (_)          | |                          */
/*		                    | |  __| |__) || || |  | | | |__) | __ ___   ____ _| |_ ___                     */
/*		                    | | |_ |  ___/ | || |  | | |  ___/ '__| \ \ / / _` | __/ _ \                    */
/*		                    | |__| | |    _| || |__| | | |   | |  | |\ V / (_| | ||  __/                    */
/*		                     \_____|_|   |_____\____/  |_|   |_|  |_| \_/ \__,_|\__\___|                    */
/*							                                                							    */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef GPIO_MCAL_PRIVATE_H_
#define GPIO_MCAL_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            	 GPIO REGISTERS DEFINITION		          		     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* GPIOA */
typedef struct
{
	volatile uint32_t CRL;			/* Port A configuration register low */
	volatile uint32_t CRH;			/* Port A configuration register high */
	volatile uint32_t IDR;			/* Port A input data register */
	volatile uint32_t ODR;			/* Port A output data register */
	volatile uint32_t BSRR;         /* Port A bit set/reset register */
	volatile uint32_t BRR;          /* Port A bit reset register */
	volatile uint32_t LCKR;         /* Port A configuration lock register */
}GPIOA_t;

#define GPIOA   ((volatile GPIOA_t*)0x40010800)

/* GPIOB */
typedef struct
{
	volatile uint32_t CRL;			/* Port B configuration register low */
	volatile uint32_t CRH;			/* Port B configuration register high */
	volatile uint32_t IDR;			/* Port B input data register */
	volatile uint32_t ODR;			/* Port B output data register */
	volatile uint32_t BSRR;         /* Port B bit set/reset register */
	volatile uint32_t BRR;          /* Port B bit reset register */
	volatile uint32_t LCKR;         /* Port B configuration lock register */
}GPIOB_t;

#define GPIOB   ((volatile GPIOB_t*)0x40010C00)

/* GPIOC */
typedef struct
{
	volatile uint32_t CRL;			/* Port C configuration register low */
	volatile uint32_t CRH;			/* Port C configuration register high */
	volatile uint32_t IDR;			/* Port C input data register */
	volatile uint32_t ODR;			/* Port C output data register */
	volatile uint32_t BSRR;         /* Port C bit set/reset register */
	volatile uint32_t BRR;          /* Port C bit reset register */
	volatile uint32_t LCKR;         /* Port C configuration lock register */
}GPIOC_t;

#define GPIOC   ((volatile GPIOC_t*)0x40011000)

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           		 PRIVATE MACROS		         	   		         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define GPIO pin mode mask  */
#define GPIO_PIN_MODE_MASK							0b1111

/* Define GPIO port mode mask  */
#define GPIO_PORT_MODE_MASK1						0x0000FFFF
#define GPIO_PORT_MODE_MASK2						0xFFFF0000

/* Define dummy macros for pin mode and initial value only for GPIO PORTC  */
#define GPIO_PORTC_PIN_DUMMY_MODE				    0000
#define GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE		    0

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            CONFIGURATION OPTIONS VALUES		       		         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Possible options of pin mode of operation */
#define INPUT_ANALOG								0000
#define INPUT_FLOATING                              0100
#define INPUT_PULLUP_PULLDOWN                       1000
#define OUTPUT_SPEED_10MHZ_PUSHPULL                 0001
#define OUTPUT_SPEED_10MHZ_OPENDRAIN                0101
#define OUTPUT_SPEED_10MHZ_AF_PUSHPULL              1001
#define OUTPUT_SPEED_10MHZ_AF_OPENDRAIN             1101
#define OUTPUT_SPEED_2MHZ_PUSHPULL                  0010
#define OUTPUT_SPEED_2MHZ_OPENDRAIN                 0110
#define OUTPUT_SPEED_2MHZ_AF_PUSHPULL               1010
#define OUTPUT_SPEED_2MHZ_AF_OPENDRAIN              1110
#define OUTPUT_SPEED_50MHZ_PUSHPULL                 0011
#define OUTPUT_SPEED_50MHZ_OPENDRAIN                0111
#define OUTPUT_SPEED_50MHZ_AF_PUSHPULL              1011
#define OUTPUT_SPEED_50MHZ_AF_OPENDRAIN             1111

/* Possible options of pin initial value */
#define LOW            								0
#define HIGH           								1
#define OPEN_DRAIN_LOW 								0
#define OPEN_DRAIN_HIGH								1
#define PULLDOWN                                    0
#define PULLUP                                      1

#endif /* GPIO_MCAL_PRIVATE_H_ */
