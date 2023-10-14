/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 7, 2023               	*/
/*      			SWC          : GPIO  			            */
/*     			    Description	 : GPIO Program                 */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						  _____ _____ _____ ____    _____                                                   */
/*						 / ____|  __ \_   _/ __ \  |  __ \                                                  */
/*						| |  __| |__) || || |  | | | |__) | __ ___   __ _ _ __ __ _ _ __ ___                */
/*						| | |_ |  ___/ | || |  | | |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \               */
/*						| |__| | |    _| || |__| | | |   | | | (_) | (_| | | | (_| | | | | | |              */
/*						 \_____|_|   |_____\____/  |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|              */
/*						                                             __/ |                                  */
/*						                          					|___/                                   */
/*----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "../Inc/standardTypes.h"
#include "../Inc/common_macros.h"

#include "../Inc/GPIO_Private.h"
#include "../Inc/GPIO_Config.h"
#include "../Inc/GPIO_Interface.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             FUNCTIONS IMPLEMENTATIONS		                     */
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
void GPIO_Init(void)
{
	/* Set GPIO Ports Modes of Operations Based on Configuration File */
	GPIOA->CRL = CONC_8_BITS(GPIO_PORTA_PIN7_MODE,GPIO_PORTA_PIN6_MODE,GPIO_PORTA_PIN5_MODE,GPIO_PORTA_PIN4_MODE,GPIO_PORTA_PIN3_MODE,GPIO_PORTA_PIN2_MODE,GPIO_PORTA_PIN1_MODE,GPIO_PORTA_PIN0_MODE);
	GPIOA->CRH = CONC_8_BITS(GPIO_PORTA_PIN15_MODE,GPIO_PORTA_PIN14_MODE,GPIO_PORTA_PIN13_MODE,GPIO_PORTA_PIN12_MODE,GPIO_PORTA_PIN11_MODE,GPIO_PORTA_PIN10_MODE,GPIO_PORTA_PIN9_MODE,GPIO_PORTA_PIN8_MODE);
	GPIOB->CRL = CONC_8_BITS(GPIO_PORTB_PIN7_MODE,GPIO_PORTB_PIN6_MODE,GPIO_PORTB_PIN5_MODE,GPIO_PORTB_PIN4_MODE,GPIO_PORTB_PIN3_MODE,GPIO_PORTB_PIN2_MODE,GPIO_PORTB_PIN1_MODE,GPIO_PORTB_PIN0_MODE);
	GPIOB->CRH = CONC_8_BITS(GPIO_PORTB_PIN15_MODE,GPIO_PORTB_PIN14_MODE,GPIO_PORTB_PIN13_MODE,GPIO_PORTB_PIN12_MODE,GPIO_PORTB_PIN11_MODE,GPIO_PORTB_PIN10_MODE,GPIO_PORTB_PIN9_MODE,GPIO_PORTB_PIN8_MODE);
	GPIOC->CRH = CONC_8_BITS(GPIO_PORTC_PIN15_MODE,GPIO_PORTC_PIN14_MODE,GPIO_PORTC_PIN13_MODE,GPIO_PORTC_PIN_DUMMY_MODE,GPIO_PORTC_PIN_DUMMY_MODE,GPIO_PORTC_PIN_DUMMY_MODE,GPIO_PORTC_PIN_DUMMY_MODE,GPIO_PORTC_PIN_DUMMY_MODE);

	/* Set GPIO Ports Initial Values Based on Configuration File */
	GPIOA->ODR = (uint32_t) CONC_16_BITS(GPIO_PORTA_PIN15_INITIAL_VALUE,GPIO_PORTA_PIN14_INITIAL_VALUE,GPIO_PORTA_PIN13_INITIAL_VALUE,GPIO_PORTA_PIN12_INITIAL_VALUE,GPIO_PORTA_PIN11_INITIAL_VALUE,GPIO_PORTA_PIN10_INITIAL_VALUE,GPIO_PORTA_PIN9_INITIAL_VALUE,GPIO_PORTA_PIN8_INITIAL_VALUE,GPIO_PORTA_PIN7_INITIAL_VALUE,GPIO_PORTA_PIN6_INITIAL_VALUE,GPIO_PORTA_PIN5_INITIAL_VALUE,GPIO_PORTA_PIN4_INITIAL_VALUE,GPIO_PORTA_PIN3_INITIAL_VALUE,GPIO_PORTA_PIN2_INITIAL_VALUE,GPIO_PORTA_PIN1_INITIAL_VALUE,GPIO_PORTA_PIN0_INITIAL_VALUE);
	GPIOB->ODR = (uint32_t) CONC_16_BITS(GPIO_PORTB_PIN15_INITIAL_VALUE,GPIO_PORTB_PIN14_INITIAL_VALUE,GPIO_PORTB_PIN13_INITIAL_VALUE,GPIO_PORTB_PIN12_INITIAL_VALUE,GPIO_PORTB_PIN11_INITIAL_VALUE,GPIO_PORTB_PIN10_INITIAL_VALUE,GPIO_PORTB_PIN9_INITIAL_VALUE,GPIO_PORTB_PIN8_INITIAL_VALUE,GPIO_PORTB_PIN7_INITIAL_VALUE,GPIO_PORTB_PIN6_INITIAL_VALUE,GPIO_PORTB_PIN5_INITIAL_VALUE,GPIO_PORTB_PIN4_INITIAL_VALUE,GPIO_PORTB_PIN3_INITIAL_VALUE,GPIO_PORTB_PIN2_INITIAL_VALUE,GPIO_PORTB_PIN1_INITIAL_VALUE,GPIO_PORTB_PIN0_INITIAL_VALUE);
	GPIOC->ODR = (uint32_t) CONC_16_BITS(GPIO_PORTC_PIN15_INITIAL_VALUE,GPIO_PORTC_PIN14_INITIAL_VALUE,GPIO_PORTC_PIN13_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE,GPIO_PORTC_PIN_DUMMY_INITIAL_VALUE);
}

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
/*					   GPIO_PIN_INPUT_PULLDOWN_PULLUP                             */
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
ERROR_STATUS_t GPIO_SetPinMode(uint8_t Copy_Port , uint8_t Copy_Pin , uint8_t Copy_Mode)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed port, pin and mode are valid or not */
	if((Copy_Port >= GPIO_PORT_A && Copy_Port <= GPIO_PORT_C) && (Copy_Pin >= GPIO_PIN_0 && Copy_Pin <= GPIO_PIN_15) &&
	   (Copy_Mode == GPIO_PIN_INPUT_ANALOG || Copy_Mode == GPIO_PIN_INPUT_FLOATING || Copy_Mode == GPIO_PIN_INPUT_PULLUP_PULLDOWN ||
		Copy_Mode == GPIO_PIN_OUTPUT_SPEED_10MHZ_PUSHPULL    || Copy_Mode == GPIO_PIN_OUTPUT_SPEED_10MHZ_OPENDRAIN    ||
		Copy_Mode == GPIO_PIN_OUTPUT_SPEED_10MHZ_AF_PUSHPULL || Copy_Mode == GPIO_PIN_OUTPUT_SPEED_10MHZ_AF_OPENDRAIN ||
		Copy_Mode == GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL     || Copy_Mode == GPIO_PIN_OUTPUT_SPEED_2MHZ_OPENDRAIN     ||
		Copy_Mode == GPIO_PIN_OUTPUT_SPEED_2MHZ_AF_PUSHPULL  || Copy_Mode == GPIO_PIN_OUTPUT_SPEED_2MHZ_AF_OPENDRAIN  ||
		Copy_Mode == GPIO_PIN_OUTPUT_SPEED_50MHZ_PUSHPULL    || Copy_Mode == GPIO_PIN_OUTPUT_SPEED_50MHZ_OPENDRAIN    ||
		Copy_Mode == GPIO_PIN_OUTPUT_SPEED_50MHZ_AF_PUSHPULL || Copy_Mode == GPIO_PIN_OUTPUT_SPEED_50MHZ_AF_OPENDRAIN))
	{
		/* Check port number */
		switch(Copy_Port)
		{
			case GPIO_PORT_A:

				/* Check pin number */
				if(Copy_Pin < 8)
				{
					/* Clear the four bits of mode concerned with the pin in CRL register */
					GPIOA->CRL &= ~(GPIO_PIN_MODE_MASK << (4*Copy_Pin));

					/* Set the four bits of mode concerned with the pin in CRL register */
					GPIOA->CRL |= (Copy_Mode << (4*Copy_Pin));
				}
				else if(Copy_Pin < 16)
				{
					/* Clear the four bits of mode concerned with the pin in CRH register */
					GPIOA->CRH &= ~(GPIO_PIN_MODE_MASK << (4*(Copy_Pin-8)));

					/* Set the four bits of mode concerned with the pin in CRH register */
					GPIOA->CRH |= (Copy_Mode << (4*(Copy_Pin-8)));
				}

				break;

			case GPIO_PORT_B:

				/* Check pin number */
				if(Copy_Pin < 8)
				{
					/* Clear the four bits of mode concerned with the pin in CRL register */
					GPIOB->CRL &= ~(GPIO_PIN_MODE_MASK << (4*Copy_Pin));

					/* Set the four bits of mode concerned with the pin in CRL register */
					GPIOB->CRL |= (Copy_Mode << (4*Copy_Pin));
				}
				else if(Copy_Pin < 16)
				{
					/* Clear the four bits of mode concerned with the pin in CRH register */
					GPIOB->CRH &= ~(GPIO_PIN_MODE_MASK << (4*(Copy_Pin-8)));

					/* Set the four bits of mode concerned with the pin in CRH register */
					GPIOB->CRH |= (Copy_Mode << (4*(Copy_Pin-8)));
				}

				break;

			case GPIO_PORT_C:

				/* Check pin number */
				if(Copy_Pin >= 13 && Copy_Pin <= 15)
				{
					/* Clear the four bits of mode concerned with the pin in CRH register */
					GPIOC->CRH &= ~(GPIO_PIN_MODE_MASK << (4*(Copy_Pin-8)));

					/* Set the four bits of mode concerned with the pin in CRH register */
					GPIOC->CRH |= (Copy_Mode << (4*(Copy_Pin-8)));
				}
				break;
		}
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}
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
ERROR_STATUS_t GPIO_SetPinVal(uint8_t Copy_Port , uint8_t Copy_Pin , uint8_t Copy_Value)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed port, pin and value are valid or not */
	if((Copy_Port >= GPIO_PORT_A && Copy_Port <= GPIO_PORT_C) && (Copy_Pin >= GPIO_PIN_0 && Copy_Pin <= GPIO_PIN_15) &&
	   (Copy_Value == GPIO_PIN_HIGH   ||  Copy_Value == GPIO_PIN_LOW    || Copy_Value == GPIO_PIN_OD_HIGH ||
	    Copy_Value == GPIO_PIN_OD_LOW ||  Copy_Value == GPIO_PIN_PULLUP || Copy_Value == GPIO_PIN_PULLDOWN))
	{
			/* Check port number */
			switch(Copy_Port)
			{
				case GPIO_PORT_A:

					/* Check value */
					if(Copy_Value == GPIO_PIN_HIGH || Copy_Value == GPIO_PIN_PULLUP || Copy_Value == GPIO_PIN_OD_HIGH)
					{
						/* Set pin in BSRR register */
						GPIOA->BSRR = (1 << Copy_Pin);
					}
					else if(Copy_Value == GPIO_PIN_LOW || Copy_Value == GPIO_PIN_PULLDOWN || Copy_Value == GPIO_PIN_OD_LOW)
					{
						/* Set pin in BRR register */
						GPIOA->BRR = (1 << Copy_Pin);
					}
					break;

				case GPIO_PORT_B:

					/* Check value */
					if(Copy_Value == GPIO_PIN_HIGH || Copy_Value == GPIO_PIN_PULLUP || Copy_Value == GPIO_PIN_OD_HIGH)
					{
						/* Set pin in BSRR register */
						GPIOB->BSRR = (1 << Copy_Pin);
					}
					else if(Copy_Value == GPIO_PIN_LOW || Copy_Value == GPIO_PIN_PULLDOWN || Copy_Value == GPIO_PIN_OD_LOW)
					{
						/* Set pin in BRR register */
						GPIOB->BRR = (1 << Copy_Pin);
					}
					break;

				case GPIO_PORT_C:

					/* Check value */
					if(Copy_Value == GPIO_PIN_HIGH || Copy_Value == GPIO_PIN_PULLUP || Copy_Value == GPIO_PIN_OD_HIGH)
					{
						/* Set pin in BSRR register */
						GPIOC->BSRR = (1 << Copy_Pin);
					}
					else if(Copy_Value == GPIO_PIN_LOW || Copy_Value == GPIO_PIN_PULLDOWN || Copy_Value == GPIO_PIN_OD_LOW)
					{
						/* Set pin in BRR register */
						GPIOC->BRR = (1 << Copy_Pin);
					}
					break;
			}
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}
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
ERROR_STATUS_t GPIO_GetPinVal(uint8_t Copy_Port , uint8_t Copy_Pin , uint8_t* Copy_pValue)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed pointer is NULL pointer or not */
	if(Copy_pValue != NULL)
	{
		/* Check if passed port and pin are valid or not */
		if((Copy_Port >= GPIO_PORT_A && Copy_Port <= GPIO_PORT_C) && (Copy_Pin >= GPIO_PIN_0 && Copy_Pin <= GPIO_PIN_15))
		{
				/* Check port number */
				switch(Copy_Port)
				{
					case GPIO_PORT_A:

						/* Get pin value in IDR register */
						*Copy_pValue = READ_BIT(GPIOA->IDR,Copy_Pin);
						break;

					case GPIO_PORT_B:

						/* Get pin value in IDR register */
						*Copy_pValue = READ_BIT(GPIOB->IDR,Copy_Pin);
						break;

					case GPIO_PORT_C:

						/* Get pin value in IDR register */
						*Copy_pValue = READ_BIT(GPIOC->IDR,Copy_Pin);
						break;
				}
		}
		else
		{
			/* Function is not behaving as expected */
			Local_Status = RT_NOK;
		}
	}
	else
	{
		/* Set function status as null pointer */
		Local_Status = NULL_POINTER;
	}

	return Local_Status;
}
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
ERROR_STATUS_t GPIO_TogglePinVal(uint8_t Copy_Port , uint8_t Copy_Pin)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed port and pin are valid or not */
	if((Copy_Port >= GPIO_PORT_A && Copy_Port <= GPIO_PORT_C) && (Copy_Pin >= GPIO_PIN_0 && Copy_Pin <= GPIO_PIN_15))
	{
			/* Check port number */
			switch(Copy_Port)
			{
				case GPIO_PORT_A:

					/* Toggle pin in ODR register */
					TOGGLE_BIT(GPIOA->ODR,Copy_Pin);
					break;

				case GPIO_PORT_B:

					/* Toggle pin in ODR register */
					TOGGLE_BIT(GPIOB->ODR,Copy_Pin);
					break;

				case GPIO_PORT_C:

					/* Toggle pin in ODR register */
					TOGGLE_BIT(GPIOC->ODR,Copy_Pin);
					break;
			}
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

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
ERROR_STATUS_t GPIO_SetPortMode(uint8_t Copy_Port , uint32_t Copy_Mode)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed port and mode are valid or not */
	if((Copy_Port >= GPIO_PORT_A && Copy_Port <= GPIO_PORT_C) && (Copy_Mode >= 0x00000000 && Copy_Mode <= 0xFFFFFFFF))
	{
			/* Check port number */
			switch(Copy_Port)
			{
				case GPIO_PORT_A:

					/* Set Port Mode */
					GPIOA->CRL = (uint16_t)(GPIO_PORT_MODE_MASK1 & Copy_Mode);
					GPIOA->CRH = (uint16_t)((GPIO_PORT_MODE_MASK2 & Copy_Mode) >> 16);
					break;

				case GPIO_PORT_B:

					/* Set Port Mode */
					GPIOB->CRL = (uint16_t)(GPIO_PORT_MODE_MASK1 & Copy_Mode);
					GPIOB->CRH = (uint16_t)((GPIO_PORT_MODE_MASK2 & Copy_Mode) >> 16);
					break;

				case GPIO_PORT_C:

					/* Set Port Mode */
					GPIOC->CRH = (uint16_t)((GPIO_PORT_MODE_MASK2 & Copy_Mode) >> 16);
					break;
			}
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}
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
ERROR_STATUS_t GPIO_SetPortVal(uint8_t Copy_Port , uint16_t Copy_Value)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed port and value are valid or not */
	if((Copy_Port >= GPIO_PORT_A && Copy_Port <= GPIO_PORT_C) && (Copy_Value >= 0x0000 && Copy_Value <= 0xFFFF))
	{
			/* Check port number */
			switch(Copy_Port)
			{
				case GPIO_PORT_A:

					/* Set Port Value */
					GPIOA->ODR = Copy_Value;
					break;

				case GPIO_PORT_B:

					/* Set Port Value */
					GPIOB->ODR = Copy_Value;
					break;

				case GPIO_PORT_C:

					/* Set Port Value */
					GPIOC->ODR = Copy_Value;
					break;
			}
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}
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
ERROR_STATUS_t GPIO_GetPortVal(uint8_t Copy_Port , uint16_t* Copy_pValue)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	/* Check if passed pointer is NULL pointer or not */
	if(Copy_pValue != NULL)
	{
		/* Check if passed port is valid or not */
		if((Copy_Port >= GPIO_PORT_A && Copy_Port <= GPIO_PORT_C))
		{
				/* Check port number */
				switch(Copy_Port)
				{
					case GPIO_PORT_A:

						/* Get port value in IDR register */
						*Copy_pValue = (uint16_t)GPIOA->IDR;
						break;

					case GPIO_PORT_B:

						/* Get port value in IDR register */
						*Copy_pValue = (uint16_t)GPIOB->IDR;
						break;

					case GPIO_PORT_C:

						/* Get port value in IDR register */
						*Copy_pValue = (uint16_t)GPIOC->IDR;
						break;
				}
		}
		else
		{
			/* Function is not behaving as expected */
			Local_Status = RT_NOK;
		}
	}
	else
	{
		/* Set function status as null pointer */
		Local_Status = NULL_POINTER;
	}

	return Local_Status;
}
