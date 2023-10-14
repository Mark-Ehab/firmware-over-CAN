/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 7, 2023               	*/
/*      			SWC          : GPIO  			            */
/*     			    Description	 : GPIO Config                  */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*							   _____ _____ _____ ____     _____             __ _                            */
/*							  / ____|  __ \_   _/ __ \   / ____|           / _(_)                           */
/*							 | |  __| |__) || || |  | | | |     ___  _ __ | |_ _  __ _                      */
/*							 | | |_ |  ___/ | || |  | | | |    / _ \| '_ \|  _| |/ _` |                     */
/*							 | |__| | |    _| || |__| | | |___| (_) | | | | | | | (_| |                     */
/*							  \_____|_|   |_____\____/   \_____\___/|_| |_|_| |_|\__, |                     */
/*							                                                     __/  |                     */
/*			                                                                     |___/                      */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef GPIO_MCAL_CONFIG_H_
#define GPIO_MCAL_CONFIG_H_

/*-------------------------------------------------------*/
/* Set the mode of operation for each pin of 			 */
/* STM32F103C8T6 (BluePill) ports :-					 */
/*                                                       */
/* Options: - INPUT_ANALOG                               */
/*			- INPUT_FLOATING                             */
/*			- INPUT_PULLUP_PULLDOWN                      */
/*			- OUTPUT_SPEED_10MHZ_PUSHPULL                */
/*          - OUTPUT_SPEED_10MHZ_OPENDRAIN               */
/*          - OUTPUT_SPEED_10MHZ_AF_PUSHPULL             */
/*          - OUTPUT_SPEED_10MHZ_AF_OPENDRAIN            */
/*		    - OUTPUT_SPEED_2MHZ_PUSHPULL                 */
/*          - OUTPUT_SPEED_2MHZ_OPENDRAIN                */
/*          - OUTPUT_SPEED_2MHZ_AF_PUSHPULL              */
/*          - OUTPUT_SPEED_2MHZ_AF_OPENDRAIN             */
/*          - OUTPUT_SPEED_50MHZ_PUSHPULL                */
/*          - OUTPUT_SPEED_50MHZ_OPENDRAIN               */
/*          - OUTPUT_SPEED_50MHZ_AF_PUSHPULL             */
/*          - OUTPUT_SPEED_50MHZ_AF_OPENDRAIN            */
/*														 */
/*-------------------------------------------------------*/

/* GPIOA */
#define GPIO_PORTA_PIN0_MODE                  INPUT_ANALOG
#define GPIO_PORTA_PIN1_MODE                  INPUT_ANALOG
#define GPIO_PORTA_PIN2_MODE                  INPUT_ANALOG
#define GPIO_PORTA_PIN3_MODE                  INPUT_ANALOG
#define GPIO_PORTA_PIN4_MODE                  INPUT_ANALOG
#define GPIO_PORTA_PIN5_MODE                  INPUT_ANALOG
#define GPIO_PORTA_PIN6_MODE                  INPUT_ANALOG
#define GPIO_PORTA_PIN7_MODE                  INPUT_ANALOG
#define GPIO_PORTA_PIN8_MODE                  INPUT_ANALOG
#define GPIO_PORTA_PIN9_MODE                  INPUT_ANALOG
#define GPIO_PORTA_PIN10_MODE                 INPUT_ANALOG
#define GPIO_PORTA_PIN11_MODE                 INPUT_ANALOG
#define GPIO_PORTA_PIN12_MODE                 INPUT_ANALOG
#define GPIO_PORTA_PIN13_MODE                 INPUT_ANALOG
#define GPIO_PORTA_PIN14_MODE                 INPUT_ANALOG
#define GPIO_PORTA_PIN15_MODE                 INPUT_ANALOG

/* GPIOB */
#define GPIO_PORTB_PIN0_MODE                  INPUT_ANALOG
#define GPIO_PORTB_PIN1_MODE                  INPUT_ANALOG
#define GPIO_PORTB_PIN2_MODE                  INPUT_ANALOG
#define GPIO_PORTB_PIN3_MODE                  INPUT_ANALOG
#define GPIO_PORTB_PIN4_MODE                  INPUT_ANALOG
#define GPIO_PORTB_PIN5_MODE                  INPUT_ANALOG
#define GPIO_PORTB_PIN6_MODE                  INPUT_ANALOG
#define GPIO_PORTB_PIN7_MODE                  INPUT_ANALOG
#define GPIO_PORTB_PIN8_MODE                  INPUT_ANALOG
#define GPIO_PORTB_PIN9_MODE                  INPUT_ANALOG
#define GPIO_PORTB_PIN10_MODE                 INPUT_ANALOG
#define GPIO_PORTB_PIN11_MODE                 INPUT_ANALOG
#define GPIO_PORTB_PIN12_MODE                 INPUT_ANALOG
#define GPIO_PORTB_PIN13_MODE                 INPUT_ANALOG
#define GPIO_PORTB_PIN14_MODE                 INPUT_ANALOG
#define GPIO_PORTB_PIN15_MODE                 INPUT_ANALOG

/* GPIOC */
#define GPIO_PORTC_PIN13_MODE                 INPUT_ANALOG
#define GPIO_PORTC_PIN14_MODE                 INPUT_ANALOG
#define GPIO_PORTC_PIN15_MODE                 INPUT_ANALOG

/*-------------------------------------------------------*/
/* Set the initial value for each pin of STM32F103C8T6   */
/* (BluePill) ports :-									 */
/*                                                       */
/* Options: - LOW                                        */
/*			- HIGH                                       */
/*			- OPEN_DRAIN_LOW                             */
/*			- OPEN_DRAIN_HIGH                            */
/*          - PULLDOWN                                   */
/*          - PULLUP                                     */
/*														 */
/*-------------------------------------------------------*/

/* GPIOA */
#define GPIO_PORTA_PIN0_INITIAL_VALUE         LOW
#define GPIO_PORTA_PIN1_INITIAL_VALUE         LOW
#define GPIO_PORTA_PIN2_INITIAL_VALUE         LOW
#define GPIO_PORTA_PIN3_INITIAL_VALUE         LOW
#define GPIO_PORTA_PIN4_INITIAL_VALUE         LOW
#define GPIO_PORTA_PIN5_INITIAL_VALUE         LOW
#define GPIO_PORTA_PIN6_INITIAL_VALUE         LOW
#define GPIO_PORTA_PIN7_INITIAL_VALUE         LOW
#define GPIO_PORTA_PIN8_INITIAL_VALUE         LOW
#define GPIO_PORTA_PIN9_INITIAL_VALUE         LOW
#define GPIO_PORTA_PIN10_INITIAL_VALUE        LOW
#define GPIO_PORTA_PIN11_INITIAL_VALUE        LOW
#define GPIO_PORTA_PIN12_INITIAL_VALUE        LOW
#define GPIO_PORTA_PIN13_INITIAL_VALUE        LOW
#define GPIO_PORTA_PIN14_INITIAL_VALUE        LOW
#define GPIO_PORTA_PIN15_INITIAL_VALUE        LOW

/* GPIOB */
#define GPIO_PORTB_PIN0_INITIAL_VALUE         LOW
#define GPIO_PORTB_PIN1_INITIAL_VALUE         LOW
#define GPIO_PORTB_PIN2_INITIAL_VALUE         LOW
#define GPIO_PORTB_PIN3_INITIAL_VALUE         LOW
#define GPIO_PORTB_PIN4_INITIAL_VALUE         LOW
#define GPIO_PORTB_PIN5_INITIAL_VALUE         LOW
#define GPIO_PORTB_PIN6_INITIAL_VALUE         LOW
#define GPIO_PORTB_PIN7_INITIAL_VALUE         LOW
#define GPIO_PORTB_PIN8_INITIAL_VALUE         LOW
#define GPIO_PORTB_PIN9_INITIAL_VALUE         LOW
#define GPIO_PORTB_PIN10_INITIAL_VALUE        LOW
#define GPIO_PORTB_PIN11_INITIAL_VALUE        LOW
#define GPIO_PORTB_PIN12_INITIAL_VALUE        LOW
#define GPIO_PORTB_PIN13_INITIAL_VALUE        LOW
#define GPIO_PORTB_PIN14_INITIAL_VALUE        LOW
#define GPIO_PORTB_PIN15_INITIAL_VALUE        LOW

/* GPIOC */
#define GPIO_PORTC_PIN13_INITIAL_VALUE        LOW
#define GPIO_PORTC_PIN14_INITIAL_VALUE        LOW
#define GPIO_PORTC_PIN15_INITIAL_VALUE        LOW

#endif /* GPIO_MCAL_CONFIG_H_ */
