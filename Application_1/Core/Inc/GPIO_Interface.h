/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 7, 2023               	*/
/*      			SWC          : GPIO  			            */
/*     			    Description	 : GPIO Interface               */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						  _____ _____ _____ ____    _____       _             __                            */
/*						 / ____|  __ \_   _/ __ \  |_   _|     | |           / _|                           */
/*						| |  __| |__) || || |  | |   | |  _ __ | |_ ___ _ __| |_ __ _  ___ ___              */
/*						| | |_ |  ___/ | || |  | |   | | | '_ \| __/ _ \ '__|  _/ _` |/ __/ _ \             */
/*						| |__| | |    _| || |__| |  _| |_| | | | ||  __/ |  | || (_| | (_|  __/             */
/*						 \_____|_|   |_____\____/  |_____|_| |_|\__\___|_|  |_| \__,_|\___\___|             */
/*						                                                                                    */
/*                                                                                                     	    */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef GPIO_MCAL_INTERFACE_H_
#define GPIO_MCAL_INTERFACE_H_

/*---------------------------------------------------------------------------------------------------------*/
/*																										   */
/* 	Note	: In STM32F103C8T6 (Bluepill) there are only three GPIO ports and number of pins in each GPIO  */
/*			  port is as follows:                                                                          */
/* 																								   		   */
/*		 	- GPIO A (Port A) --> 16 pins (From PIN_0 to PIN_15)                                           */
/*		 	- GPIO B (Port B) --> 16 pins (From PIN_0 to PIN_15)                                           */
/*		 	- GPIO C (Port C) --> 3 pins  (From PIN_13 to PIN_15)                                          */
/*                                                                                                         */
/* 	Note	: The number of ports and pins in each port varies depending on STM version used    		   */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	    INTERFACE MACROS		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
/* Available Ports */
#define GPIO_PORT_A									  0U
#define GPIO_PORT_B                                   1U
#define GPIO_PORT_C                                   2U

/* Available Pins */
#define GPIO_PIN_0                                    0U
#define GPIO_PIN_1                                    1U
#define GPIO_PIN_2                                    2U
#define GPIO_PIN_3                                    3U
#define GPIO_PIN_4                                    4U
#define GPIO_PIN_5                                    5U
#define GPIO_PIN_6                                    6U
#define GPIO_PIN_7                                    7U
#define GPIO_PIN_8                                    8U
#define GPIO_PIN_9                                    9U
#define GPIO_PIN_10                                   10U
#define GPIO_PIN_11                                   11U
#define GPIO_PIN_12                                   12U
#define GPIO_PIN_13                                   13U
#define GPIO_PIN_14                                   14U
#define GPIO_PIN_15                                   15U

/****************GPIO Modes of Operation****************/

/* GPIO Input Modes */

/*******************************Pin Level*******************************/
#define GPIO_PIN_INPUT_ANALOG          						0b0000
#define GPIO_PIN_INPUT_FLOATING        						0b0100
#define GPIO_PIN_INPUT_PULLUP_PULLDOWN 						0b1000

/*******************************Port Level*******************************/
#define GPIO_PORT_FULL_INPUT_ANALOG          				0x00000000
#define GPIO_PORT_FULL_INPUT_FLOATING        				0x44444444
#define GPIO_PORT_FULL_INPUT_PULLUP_PULLDOWN  				0x88888888

/* GPIO Output Modes at 10 MHz Speed */

/*******************************Pin Level*******************************/
#define GPIO_PIN_OUTPUT_SPEED_10MHZ_PUSHPULL				0b0001
#define GPIO_PIN_OUTPUT_SPEED_10MHZ_OPENDRAIN				0b0101
#define GPIO_PIN_OUTPUT_SPEED_10MHZ_AF_PUSHPULL     		0b1001
#define GPIO_PIN_OUTPUT_SPEED_10MHZ_AF_OPENDRAIN			0b1101

/*******************************Port Level*******************************/
#define GPIO_PORT_FULL_OUTPUT_SPEED_10MHZ_PUSHPULL			0x11111111
#define GPIO_PORT_FULL_OUTPUT_SPEED_10MHZ_OPENDRAIN			0x55555555
#define GPIO_PORT_FULL_OUTPUT_SPEED_10MHZ_AF_PUSHPULL     	0x99999999
#define GPIO_PORT_FULL_OUTPUT_SPEED_10MHZ_AF_OPENDRAIN		0xDDDDDDDD

/* GPIO Output Modes at 2 MHz Speed */

/*******************************Pin Level*******************************/
#define GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL					0b0010
#define GPIO_PIN_OUTPUT_SPEED_2MHZ_OPENDRAIN       			0b0110
#define GPIO_PIN_OUTPUT_SPEED_2MHZ_AF_PUSHPULL      		0b1010
#define GPIO_PIN_OUTPUT_SPEED_2MHZ_AF_OPENDRAIN     		0b1110

/*******************************Port Level*******************************/
#define GPIO_PORT_FULL_OUTPUT_SPEED_2MHZ_PUSHPULL			0x22222222
#define GPIO_PORT_FULL_OUTPUT_SPEED_2MHZ_OPENDRAIN        	0x66666666
#define GPIO_PORT_FULL_OUTPUT_SPEED_2MHZ_AF_PUSHPULL      	0xAAAAAAAA
#define GPIO_PORT_FULL_OUTPUT_SPEED_2MHZ_AF_OPENDRAIN     	0xEEEEEEEE

/* GPIO Output Modes at 50 MHz Speed */

/*******************************Pin Level*******************************/
#define GPIO_PIN_OUTPUT_SPEED_50MHZ_PUSHPULL        		0b0011
#define GPIO_PIN_OUTPUT_SPEED_50MHZ_OPENDRAIN       		0b0111
#define GPIO_PIN_OUTPUT_SPEED_50MHZ_AF_PUSHPULL     		0b1011
#define GPIO_PIN_OUTPUT_SPEED_50MHZ_AF_OPENDRAIN    		0b1111

/*******************************Port Level*******************************/
#define GPIO_PORT_FULL_OUTPUT_SPEED_50MHZ_PUSHPULL        	0x33333333
#define GPIO_PORT_FULL_OUTPUT_SPEED_50MHZ_OPENDRAIN       	0x77777777
#define GPIO_PORT_FULL_OUTPUT_SPEED_50MHZ_AF_PUSHPULL     	0xBBBBBBBB
#define GPIO_PORT_FULL_OUTPUT_SPEED_50MHZ_AF_OPENDRAIN      0xFFFFFFFF


/****************Possible Pin Values in Output Modes of Various Speeds (Frequencies)****************/

/* Push-Pull Mode */
#define GPIO_PIN_HIGH										1U		/* Set MC VCC on the Pin */
#define GPIO_PIN_LOW										0U		/* Set 0V on the Pin */

/* Open-Drain Mode */
#define GPIO_PIN_OD_HIGH									1U		/* Make the MC Pin Floating */
#define GPIO_PIN_OD_LOW										0U		/* Set 0V on the Pin */

/* Possible Pin Values in PULL_UP or PULL_DOWN Input Mode (PULL_UP Resistor or PULL_DOWN Resistor) */
#define GPIO_PIN_PULLUP										1U 		/* Connect the input pin to internal pullup resistor */
#define GPIO_PIN_PULLDOWN									0U 		/* Connect the input pin to internal pulldown resistor */

/* Common Port Values (FULL_HIGH or FULL_LOW) in PUSHULL Output Modes of Various Speeds (Frequencies) */
#define GPIO_FULL_HIGH										0xFFFF	/* Set the port value to full high */
#define GPIO_FULL_LOW										0x0000  /* Set the port value to full low */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  FUNCTIONS PROTOTYPES		          	             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: Init          					                              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Initializes GPIO pins and ports through setting their modes    */
/* 				   and their initial values based on configuration file        	  */
/*--------------------------------------------------------------------------------*/
void GPIO_Init(void);


/*******************************Pin Level*******************************/

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetPinMode          					                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Port				                              */
/*				   Ex:(GPIO_PORT_A, GPIO_PORT_B, GPIO_PORT_C)					  */
/*				   uint8_t Copy_Pin												  */
/*				   Ex:(GPIO_PIN_0 ... GPIO_PIN_15)								  */
/*				   uint8_t Copy_Mode                                              */
/*				   Ex: GPIO_PIN_INPUT_ANALOG                                      */
/*					   GPIO_PIN_INPUT_FLOATING                                    */
/*					   GPIO_PIN_INPUT_PULLUP_PULLDOWN                             */
/*					   GPIO_PIN_OUTPUT_SPEED_10MHZ_PUSHPULL                       */
/*				       GPIO_PIN_OUTPUT_SPEED_10MHZ_OPENDRAIN                      */
/*				       GPIO_PIN_OUTPUT_SPEED_10MHZ_AF_PUSHPULL                    */
/*				       GPIO_PIN_OUTPUT_SPEED_10MHZ_AF_OPENDRAIN                   */
/*					   GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL                        */
/*				       GPIO_PIN_OUTPUT_SPEED_2MHZ_OPENDRAIN                       */
/*				       GPIO_PIN_OUTPUT_SPEED_2MHZ_AF_PUSHPULL                     */
/*				       GPIO_PIN_OUTPUT_SPEED_2MHZ_AF_OPENDRAIN                    */
/*					   GPIO_PIN_OUTPUT_SPEED_50MHZ_PUSHPULL                       */
/*				       GPIO_PIN_OUTPUT_SPEED_50MHZ_OPENDRAIN                      */
/*				       GPIO_PIN_OUTPUT_SPEED_50MHZ_AF_PUSHPULL                    */
/*				       GPIO_PIN_OUTPUT_SPEED_50MHZ_AF_OPENDRAIN                   */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Sets the mode of operation of GPIO pin                         */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t GPIO_SetPinMode(uint8_t Copy_Port , uint8_t Copy_Pin , uint8_t Copy_Mode);

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetPinVal         					                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Port											  */
/*				   Ex:(GPIO_PORT_A, GPIO_PORT_B, GPIO_PORT_C)					  */
/*				   uint8_t Copy_Pin												  */
/*				   Ex:(GPIO_PIN_0 ... GPIO_PIN_15)								  */
/* 				   uint8_t Copy_Value                                             */
/*                 Ex: GPIO_PIN_HIGH                                              */
/*                     GPIO_PIN_LOW                                               */
/*                     GPIO_PIN_OD_HIGH                                           */
/*                     GPIO_PIN_OD_LOW                                            */
/*                     GPIO_PIN_PULLUP                                            */
/*                     GPIO_PIN_PULLDOWN                                          */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Sets a value (Logical High or Logical Low) on GPIO pin         */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t GPIO_SetPinVal(uint8_t Copy_Port , uint8_t Copy_Pin , uint8_t Copy_Value);

/*--------------------------------------------------------------------------------*/
/* @Function Name: GetPinVal         					                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Port											  */
/*				   Ex:(GPIO_PORT_A, GPIO_PORT_B, GPIO_PORT_C)					  */
/*				   uint8_t Copy_Pin												  */
/*				   Ex:(GPIO_PIN_0 ... GPIO_PIN_15)								  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : uint8_t* Copy_pValue                                           */
/*				   Ex: GPIO_PIN_HIGH											  */
/*					   GPIO_PIN_LOW	 											  */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Gets the value (Logical High or Logical Low) on GPIO pin       */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t GPIO_GetPinVal(uint8_t Copy_Port , uint8_t Copy_Pin , uint8_t* Copy_pValue);

/*--------------------------------------------------------------------------------*/
/* @Function Name: TogglePinVal         			                              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Port											  */
/*				   Ex:(GPIO_PORT_A, GPIO_PORT_B, GPIO_PORT_C)					  */
/*				   uint8_t Copy_Pin												  */
/*				   Ex:(GPIO_PIN_0 ... GPIO_PIN_15)								  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : toggles the value on GPIO pin						          */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t GPIO_TogglePinVal(uint8_t Copy_Port , uint8_t Copy_Pin);


/*******************************Port Level*******************************/

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetPortMode          			                              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Port											  */
/*				   Ex:(GPIO_PORT_A, GPIO_PORT_B, GPIO_PORT_C)					  */
/* 				   uint32_t Copy_Mode				                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Sets the mode of operation of GPIO port						  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t GPIO_SetPortMode(uint8_t Copy_Port , uint32_t Copy_Mode);

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetPortVal         					                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Port											  */
/*				   Ex:(GPIO_PORT_A, GPIO_PORT_B, GPIO_PORT_C)					  */
/* 				   uint16_t Copy_Value				                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Sets a value on GPIO port						              */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t GPIO_SetPortVal(uint8_t Copy_Port , uint16_t Copy_Value);

/*--------------------------------------------------------------------------------*/
/* @Function Name: GetPortVal	        					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Port											  */
/*				   Ex:(GPIO_PORT_A, GPIO_PORT_B, GPIO_PORT_C)					  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : uint16_t* Copy_pValue                                          */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Gets the value on GPIO port						              */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t GPIO_GetPortVal(uint8_t Copy_Port , uint16_t* Copy_pValue);

#endif /* GPIO_MCAL_INTERFACE_H_ */
