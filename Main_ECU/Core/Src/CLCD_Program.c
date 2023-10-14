/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 *          Mark Ehab Tawfik (201)
 *          Hazem Mohamed Ezzeldin (1297)
 *          Azza Saeed Mohammed Gad (912)
 *          MennaTullah Ahmed Farrag Hefny (116)
 * \date: 1/10/2023
 * \brief: source file for LCD
 ******************************************************/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "../Inc/standardTypes.h"
#include "../Inc/common_macros.h"
#include "../Inc/SERVICE_FUNCTIONS.h"

#include "../Inc/GPIO_Interface.h"

#include "../Inc/CLCD_Private.h"
#include "../Inc/CLCD_Config.h"
#include "../Inc/CLCD_Interface.h"

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*					   _____ _      _____ _____    _____                                                    */
/*					  / ____| |    / ____|  __ \  |  __ \                                                   */
/*					 | |    | |   | |    | |  | | | |__) | __ ___   __ _ _ __ __ _ _ __ ___                 */
/*					 | |    | |   | |    | |  | | |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \                */
/*					 | |____| |___| |____| |__| | | |   | | | (_) | (_| | | | (_| | | | | | |               */
/*					  \_____|______\_____|_____/  |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|               */
/*					                                                __/ |                                   */
/*					                            				   |___/                                    */
/*----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             FUNCTIONS IMPLEMENTATIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: Init							                                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Initialize Character LCD								          */
/*--------------------------------------------------------------------------------*/
void CLCD_Init(void)
{
	/* Set the direction of control pins */
	GPIO_SetPinMode(CLCD_CTRL_PINS_PORT,CLCD_E_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);
	GPIO_SetPinMode(CLCD_CTRL_PINS_PORT,CLCD_RS_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);

	/* Check Selected CLCD Mode */
	#if CLCD_MODE == FOUR_BIT_MODE

		/* Set the direction of data pins */
		GPIO_SetPinMode(CLCD_DATA_PORT,CLCD_D4_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);
		GPIO_SetPinMode(CLCD_DATA_PORT,CLCD_D5_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);
		GPIO_SetPinMode(CLCD_DATA_PORT,CLCD_D6_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);
		GPIO_SetPinMode(CLCD_DATA_PORT,CLCD_D7_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);

		/* Delay for 40 ms */
		SERV_Delay_ms(40);

		/* Set up CLCD on the 4-bit mode */
		CLCD_SetFourBitMode();

	#elif CLCD_MODE == EIGHT_BIT_MODE

		/* Set the direction of data pins */
		GPIO_SetPinMode(CLCD_DATA_PORT,CLCD_D0_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);
		GPIO_SetPinMode(CLCD_DATA_PORT,CLCD_D1_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);
		GPIO_SetPinMode(CLCD_DATA_PORT,CLCD_D2_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);
		GPIO_SetPinMode(CLCD_DATA_PORT,CLCD_D3_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);
		GPIO_SetPinMode(CLCD_DATA_PORT,CLCD_D4_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);
		GPIO_SetPinMode(CLCD_DATA_PORT,CLCD_D5_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);
		GPIO_SetPinMode(CLCD_DATA_PORT,CLCD_D6_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);
		GPIO_SetPinMode(CLCD_DATA_PORT,CLCD_D7_PIN,GPIO_PIN_OUTPUT_SPEED_2MHZ_PUSHPULL);

		/* Delay for 40 ms */
		SERV_Delay_ms(40);

		/* Set up CLCD on the 8-bit mode */
		CLCD_SetEightBitMode();

	#else

		#error "Wrong CLCD Mode Configuration"

	#endif

	/* Delay for 1 ms */
	SERV_Delay_ms(1);

	/* Display on CLCD and turn off cursor */
	CLCD_DisplayOnCursorOff();

	/* Delay for 1 ms */
	SERV_Delay_ms(1);

	/* Clear CLCD */
	CLCD_ClearDisplay();

	/* Delay for 3 ms */
	SERV_Delay_ms(3);

	/* Setting up CLCD on entry mode */
	CLCD_SetEntryMode();

	/* Delay for 1 ms */
	SERV_Delay_ms(1);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: SendCommand							                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Command				                              */
/*                 Brief: Command to be sent to CLCD controller to perform        */
/*						  operation on CLCD                                       */
/*                 Range: - CLCD_FUNCTION_SET_EIGHT_BIT_MODE_CMD                  */
/*						  - CLCD_FUNCTION_SET_FOUR_BIT_MODE_CMD                   */
/*						  - CLCD_DISPLAY_ON_CURSOR_OFF_CMD   	                  */
/*						  - CLCD_DISPLAY_OFF_CURSOR_OFF_CMD    	                  */
/*						  - CLCD_DISPLAY_ON_CURSOR_ON_CMD   	                  */
/*						  - CLCD_DISPLAY_OFF_CURSOR_ON_CMD    	                  */
/*						  - CLCD_BLINK_CURSOR_CMD				                  */
/*						  - CLCD_SHIFT_LEFT_CURSOR_CMD			                  */
/*						  - CLCD_SHIFT_RIGHT_CURSOR_CMD			                  */
/*						  - CLCD_SHIFT_LEFT_DISPLAY_CMD			                  */
/*						  - CLCD_SHIFT_RIGHT_DISPLAY_CMD		                  */
/*						  - CLCD_BEGIN_AT_FIRST_LINE_CMD		                  */
/*						  - CLCD_BEGIN_AT_SECOND_LINE_CMD		                  */
/*						  - CLCD_DISPLAY_CLEAR_CMD 				                  */
/*						  - CLCD_ENTRY_MODE_CMD					                  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Send a command to Character LCD controller	                  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_SendCommand(uint8_t Copy_Command)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK ;
	uint8_t Local_Bit0 , Local_Bit1 , Local_Bit2 , Local_Bit3 , Local_Bit4 , Local_Bit5 , Local_Bit6 , Local_Bit7;

	/* Check if passed command is valid or not */
	if(Copy_Command == CLCD_FUNCTION_SET_EIGHT_BIT_MODE_CMD || Copy_Command == CLCD_FUNCTION_SET_FOUR_BIT_MODE_CMD  ||
       Copy_Command == CLCD_DISPLAY_ON_CURSOR_OFF_CMD   	|| Copy_Command == CLCD_DISPLAY_OFF_CURSOR_OFF_CMD    	||
       Copy_Command == CLCD_DISPLAY_ON_CURSOR_ON_CMD   	    || Copy_Command == CLCD_DISPLAY_OFF_CURSOR_ON_CMD    	||
	   Copy_Command == CLCD_BLINK_CURSOR_CMD				|| Copy_Command == CLCD_SHIFT_LEFT_CURSOR_CMD			||
	   Copy_Command == CLCD_SHIFT_RIGHT_CURSOR_CMD			|| Copy_Command == CLCD_SHIFT_LEFT_DISPLAY_CMD			||
       Copy_Command == CLCD_SHIFT_RIGHT_DISPLAY_CMD		    || Copy_Command == CLCD_BEGIN_AT_FIRST_LINE_CMD		    ||
       Copy_Command == CLCD_BEGIN_AT_SECOND_LINE_CMD		|| Copy_Command == CLCD_DISPLAY_CLEAR_CMD 				||
       Copy_Command == CLCD_ENTRY_MODE_CMD)
	{
		/* Set RS to LOW to tell CLCD to receive a command */
		GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_RS_PIN , GPIO_PIN_LOW);

		/* Delay for 1 ms */
		SERV_Delay_ms(1);

		/* Set E to LOW tell CLCD to stop reading the command */
		GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_LOW);

		/* Delay for 1 ms */
		SERV_Delay_ms(1);

		/* Check Selected CLCD Mode */
		#if CLCD_MODE == FOUR_BIT_MODE

			/* Get command most significant bits */
			Local_Bit7 = READ_BIT(Copy_Command,7);
			Local_Bit6 = READ_BIT(Copy_Command,6);
			Local_Bit5 = READ_BIT(Copy_Command,5);
			Local_Bit4 = READ_BIT(Copy_Command,4);

			/* Set E to HIGH tell CLCD to start reading the command */
			GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_HIGH);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Set command most significant bits on CLCD data port */
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D7_PIN,Local_Bit7);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D6_PIN,Local_Bit6);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D5_PIN,Local_Bit5);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D4_PIN,Local_Bit4);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Set E to LOW tell CLCD to stop reading the command */
			GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_LOW);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Get command least significant bits */
			Local_Bit3 = READ_BIT(Copy_Command,3);
			Local_Bit2 = READ_BIT(Copy_Command,2);
			Local_Bit1 = READ_BIT(Copy_Command,1);
			Local_Bit0 = READ_BIT(Copy_Command,0);

			/* Set E to HIGH tell CLCD to start reading the command */
			GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_HIGH);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Set command least significant bits on CLCD data port */
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D7_PIN,Local_Bit3);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D6_PIN,Local_Bit2);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D5_PIN,Local_Bit1);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D4_PIN,Local_Bit0);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Clear E to tell CLCD to stop reading the command */
			GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_LOW);

			/* Delay for 2 ms */
			SERV_Delay_ms(2);

		#elif CLCD_MODE == EIGHT_BIT_MODE

			/* Get command bits */
			Local_Bit7 = READ_BIT(Copy_Command,7);
			Local_Bit6 = READ_BIT(Copy_Command,6);
			Local_Bit5 = READ_BIT(Copy_Command,5);
			Local_Bit4 = READ_BIT(Copy_Command,4);
			Local_Bit3 = READ_BIT(Copy_Command,3);
			Local_Bit2 = READ_BIT(Copy_Command,2);
			Local_Bit1 = READ_BIT(Copy_Command,1);
			Local_Bit0 = READ_BIT(Copy_Command,0);

			/* Set E to HIGH tell CLCD to start reading the command */
			GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_HIGH);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Set command bits on CLCD data port */
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D7_PIN,Local_Bit7);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D6_PIN,Local_Bit6);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D5_PIN,Local_Bit5);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D4_PIN,Local_Bit4);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D3_PIN,Local_Bit3);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D2_PIN,Local_Bit2);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D1_PIN,Local_Bit1);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D0_PIN,Local_Bit0);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Set E to LOW tell CLCD to stop reading the command */
			GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_LOW);

			/* Delay for 2 ms */
			SERV_Delay_ms(2);

		#else

			#error "Wrong CLCD Mode Configuration"

		#endif

	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: WriteCharacter							                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Character				                          */
/*                 Brief: Character to be written on CLCD display 				  */
/*                 Range: Any value can be represented in 1 byte                  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Write a character on Character CLCD		                      */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_WriteCharacter(uint8_t Copy_Character)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK ;
#if CLCD_MODE == EIGHT_BIT_MODE
	uint8_t Local_Bit0 , Local_Bit1 , Local_Bit2 , Local_Bit3;
#endif
	uint8_t Local_Bit4 , Local_Bit5 , Local_Bit6 , Local_Bit7;

	/* Check if passed command is valid or not */
	if(Copy_Character >= 0 && Copy_Character <= 255)
	{
		/* Set RS to HIGH to tell CLCD to receive character */
		GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_RS_PIN , GPIO_PIN_HIGH);

		/* Delay for 1 ms */
		SERV_Delay_ms(1);

		/* Set E to LOW tell CLCD to stop reading the character */
		GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_LOW);

		/* Delay for 1 ms */
		SERV_Delay_ms(1);

		/* Check Selected CLCD Mode */
		#if CLCD_MODE == FOUR_BIT_MODE

			/* Get character most significant bits */
			Local_Bit7 = READ_BIT(Copy_Character,7);
			Local_Bit6 = READ_BIT(Copy_Character,6);
			Local_Bit5 = READ_BIT(Copy_Character,5);
			Local_Bit4 = READ_BIT(Copy_Character,4);

			/* Set E to HIGH tell CLCD to start reading the character */
			GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_HIGH);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Set character most significant bits on CLCD data port */
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D7_PIN,Local_Bit7);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D6_PIN,Local_Bit6);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D5_PIN,Local_Bit5);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D4_PIN,Local_Bit4);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Set E to LOW tell CLCD to stop reading the character */
			GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_LOW);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Get character least significant bits */
			Local_Bit7 = READ_BIT(Copy_Character,3);
			Local_Bit6 = READ_BIT(Copy_Character,2);
			Local_Bit5 = READ_BIT(Copy_Character,1);
			Local_Bit4 = READ_BIT(Copy_Character,0);

			/* Set E to HIGH tell CLCD to start reading the character */
			GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_HIGH);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Set character least significant bits on CLCD data port */
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D7_PIN,Local_Bit7);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D6_PIN,Local_Bit6);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D5_PIN,Local_Bit5);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D4_PIN,Local_Bit4);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Clear E to tell CLCD to stop reading the character */
			GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_LOW);

			/* Delay for 2 ms */
			SERV_Delay_ms(2);

		#elif CLCD_MODE == EIGHT_BIT_MODE

			/* Get character bits */
			Local_Bit7 = READ_BIT(Copy_Character,7);
			Local_Bit6 = READ_BIT(Copy_Character,6);
			Local_Bit5 = READ_BIT(Copy_Character,5);
			Local_Bit4 = READ_BIT(Copy_Character,4);
			Local_Bit3 = READ_BIT(Copy_Character,3);
			Local_Bit2 = READ_BIT(Copy_Character,2);
			Local_Bit1 = READ_BIT(Copy_Character,1);
			Local_Bit0 = READ_BIT(Copy_Character,0);

			/* Set E to HIGH tell CLCD to start reading the character */
			GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_HIGH);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Set character bits on CLCD data port */
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D7_PIN,Local_Bit7);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D6_PIN,Local_Bit6);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D5_PIN,Local_Bit5);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D4_PIN,Local_Bit4);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D3_PIN,Local_Bit3);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D2_PIN,Local_Bit2);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D1_PIN,Local_Bit1);
			GPIO_SetPinVal(CLCD_DATA_PORT,CLCD_D0_PIN,Local_Bit0);

			/* Delay for 1 ms */
			SERV_Delay_ms(1);

			/* Set E to LOW tell CLCD to stop reading the character */
			GPIO_SetPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , GPIO_PIN_LOW);

			/* Delay for 2 ms */
			SERV_Delay_ms(2);

		#else

			#error "Wrong CLCD Mode Configuration"

		#endif
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetEightBitMode							                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Set up Character LCD on 8-bit mode							  */
/*--------------------------------------------------------------------------------*/
void CLCD_SetEightBitMode(void)
{
	CLCD_SendCommand(CLCD_FUNCTION_SET_EIGHT_BIT_MODE_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetFourBitMode							                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Set up Character LCD on 4-bit mode							  */
/*--------------------------------------------------------------------------------*/
void CLCD_SetFourBitMode(void)
{
	 CLCD_SendCommand(CLCD_FUNCTION_SET_FOUR_BIT_MODE_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: DisplayOnCursorOff							                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Turn on display and turn off cursor							  */
/*--------------------------------------------------------------------------------*/
void CLCD_DisplayOnCursorOff(void)
{
	 CLCD_SendCommand(CLCD_DISPLAY_ON_CURSOR_OFF_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: DisplayOffCursorOff							                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Turn off display and turn off cursor							  */
/*--------------------------------------------------------------------------------*/
void CLCD_DisplayOffCursorOff(void)
{
	 CLCD_SendCommand(CLCD_DISPLAY_OFF_CURSOR_OFF_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: DisplayOnCursorOn							                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Turn on display and turn on cursor							  */
/*--------------------------------------------------------------------------------*/
void CLCD_DisplayOnCursorOn(void)
{
	 CLCD_SendCommand(CLCD_DISPLAY_ON_CURSOR_ON_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: DisplayOffCursorOn							                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Turn off display and turn on cursor							  */
/*--------------------------------------------------------------------------------*/
void CLCD_DisplayOffCursorOn(void)
{
	CLCD_SendCommand(CLCD_DISPLAY_OFF_CURSOR_ON_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: BlinkCursor									                  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Blink the cursor of Character LCD							  */
/*--------------------------------------------------------------------------------*/
void CLCD_BlinkCursor(void)
{
	CLCD_SendCommand(CLCD_BLINK_CURSOR_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: ShiftLeftCursor									              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Shift left the cursor of Character LCD						  */
/*--------------------------------------------------------------------------------*/
void CLCD_ShiftLeftCursor(void)
{
	CLCD_SendCommand(CLCD_SHIFT_LEFT_CURSOR_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: ShiftRightCursor									              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Shift right the cursor of Character LCD						  */
/*--------------------------------------------------------------------------------*/
void CLCD_ShiftRightCursor(void)
{
	CLCD_SendCommand(CLCD_SHIFT_RIGHT_CURSOR_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: ShiftDisplayLeft									              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Shift left the entire display of Character LCD				  */
/*--------------------------------------------------------------------------------*/
void CLCD_ShiftDisplayLeft(void)
{
	CLCD_SendCommand(CLCD_SHIFT_LEFT_DISPLAY_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: ShiftDisplayRight									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Shift right the entire display of Character LCD				  */
/*--------------------------------------------------------------------------------*/
void CLCD_ShiftDisplayRight(void)
{
	CLCD_SendCommand(CLCD_SHIFT_RIGHT_DISPLAY_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: BeginAtFirstLine 									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Force cursor to be at the beginning of the first line		  */
/*--------------------------------------------------------------------------------*/
void CLCD_BeginAtFirstLine(void)
{
	CLCD_SendCommand(CLCD_BEGIN_AT_FIRST_LINE_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: BeginAtSecondLine 									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Force cursor to be at the beginning of the second line		  */
/*--------------------------------------------------------------------------------*/
void CLCD_BeginAtSecondLine(void)
{
	CLCD_SendCommand(CLCD_BEGIN_AT_SECOND_LINE_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: ClearDisplay     									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Clear the entire display of character LCD		 			  */
/*--------------------------------------------------------------------------------*/
void CLCD_ClearDisplay(void)
{
	CLCD_SendCommand(CLCD_DISPLAY_CLEAR_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: SetEntryMode     									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Set up character LCD to operate on the entry mode		 	  */
/*--------------------------------------------------------------------------------*/
void CLCD_SetEntryMode(void)
{
	CLCD_SendCommand(CLCD_ENTRY_MODE_CMD);
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: WriteString      									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t* Copy_pString				                          */
/*				   Brief: Pointer to character for the first character of the     */
/*                        string to be written on character LCD 	              */
/*                 Range: None                                                    */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Write a string on the Character LCD display      		 	  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_WriteString(uint8_t* Copy_pString)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK ;
	uint32_t Local_CharacterCounter = 0 ;

	/* Check if passed pointer is NULL pointer or not */
	if(Copy_pString != NULL)
	{
		/* Write the passed string on the CLCD display */
		while(Copy_pString[Local_CharacterCounter] != '\0')
		{
			/* Write a character */
			CLCD_WriteCharacter(Copy_pString[Local_CharacterCounter]);

			/* Increment the character counter */
			Local_CharacterCounter++;

			/* Check if the character counter reached 16 or not */
			if(Local_CharacterCounter == 20)
			{
				/* Force CLCD cursor to begin at second line */
				CLCD_BeginAtSecondLine();
			}
		}
	}
	else
	{
		/* Passed pointer is NULL pointer */
		Local_Status = NULL_POINTER;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: WriteNumber      									          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : sint32_t Copy_Number    				                          */
/*				   Brief: Number (Could be positive or negative) to be written on */
/*                        character LCD 	                                      */
/*                 Range: None                                                    */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Write an integer number (Could be positive or negative)        */
/*                 on the Character LCD display      	 						  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_WriteNumber(sint32_t Copy_Number)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;
	sint32_t Local_NumberCopy = Copy_Number;
	uint8_t  Local_DigitCounter = 0;
	uint8_t  Local_DigitIndex;
	uint8_t  Local_NumDigits[10];

	/* Check if passed number is within valid range or not */
	if(Copy_Number >= -2147483648 && Copy_Number <= 2147483647)
	{
		/* Check if passed number is equal to 0 or not */
		if(Copy_Number != 0)
		{
			/* Check if number is positive or not */
			if(Copy_Number < 0)
			{
				/* Write Negative Sign on CLCD */
				CLCD_WriteCharacter('-');

				/* Multiply Number by -1 to start processing then writing it on CLCD */
				Copy_Number *= -1;

				/* Multiply Number Copy by -1 */
				Local_NumberCopy *= -1;
			}

			/* Count number of digits for the passed integer */
			while(Local_NumberCopy != 0)
			{
				Local_NumberCopy = Local_NumberCopy / 10;
				Local_DigitCounter++;
			}

			/* Separate number's digits then organizing them into a char array */
			for(Local_DigitIndex = Local_DigitCounter ; Local_DigitIndex > 0 ; Local_DigitIndex--)
			{
				Local_NumDigits[Local_DigitIndex-1] = ((Copy_Number % 10) + '0');
				Copy_Number = Copy_Number / 10;
			}

			/* Write the passed number on the CLCD display */
			for(Local_DigitIndex = 0 ; Local_DigitIndex < Local_DigitCounter ; Local_DigitIndex++)
			{
				CLCD_WriteCharacter(Local_NumDigits[Local_DigitIndex]);
				SERV_Delay_ms(3);
			}
		}
		else
		{
			/* Write '0' on CLCD */
			CLCD_WriteCharacter('0');
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
/* @Function Name: SetCGRamAddress      									      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Location    				                      */
/*				   Brief: Address of CGRAM location to be pointed to	          */
/*                 Range: -	                                                      */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Force the Character LCD controller to point to a CGRAM address */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_SetCGRamAddress(uint8_t Copy_Location)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;

	if(Copy_Location < 8)
	{
		/* Order CLCD to point to desired location on CGRAM */
		CLCD_SendCommand(64 + (Copy_Location * 8));
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: WriteCustomCharactersOnCGRam      							  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t* Copy_pCharacter    				                      */
/*				   Brief: Pointer to character to be stored in CGRAM              */
/*				   Range: None	                                                  */
/*				   -------------------------------------------------------------- */
/*                 uint8_t Copy_Location                                          */
/*				   Brief: Address of CGRAM location to be pointed to	          */
/*				   Range: -											              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Add custom characters to CGRAM of Character LCD   			  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_WriteCustomCharactersOnCGRam(uint8_t* Copy_pCharacter,uint8_t Copy_Location)
{
	/* Local Variable Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;
	uint32_t Local_CharacterPatternCounter;

	/* Check if passed pointer is NULL pointer or not */
	if(Copy_pCharacter != NULL)
	{
		/* Access CGRAM location in which custom character will be written */
		CLCD_SetCGRamAddress(Copy_Location);

		/* Write custom character to selected CGRAM location through traversing over its patterns and writing it */
		for(Local_CharacterPatternCounter = 0 ; Local_CharacterPatternCounter < 8 ; Local_CharacterPatternCounter++)
		{
			/* Write each pattern of custom character to selected CGRAM location */
			CLCD_WriteCharacter(Copy_pCharacter[Local_CharacterPatternCounter]);
		}
	}
	else
	{
		/* Passed pointer is NULL pointer */
		Local_Status = NULL_POINTER;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: WriteCustomCharactersOnCGRam      							  */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_RowNumber    				                      */
/*				   Brief: CLCD row number          						          */
/*				   Range: (CLCD_ROW_0 --> CLCD_ROW_1)	                          */
/*				   -------------------------------------------------------------- */
/*                 uint8_t Copy_ColumnNumber                                      */
/*				   Brief: CLCD column number							          */
/*				   Range: (CLCD_COLUMN_0 --> CLCD_COLUMN_15)	                  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Put the cursor at a specific location (segment) on the         */
/*                 character LCD display					                      */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t CLCD_MoveCursor(uint8_t Copy_RowNumber , uint8_t Copy_ColumnNumber)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK ;

	/* Check if passed column number is within valid range or not */
	if((Copy_ColumnNumber >= 0) && (Copy_ColumnNumber <= 19))
	{
		switch(Copy_RowNumber)
		{
			case 0:

				/* Move the cursor to desired cell number on row 0 */
				CLCD_SendCommand(Copy_ColumnNumber+0x80);
				break;

			case 1:

				/* Move the cursor to desired cell number on row 1 */
				CLCD_SendCommand(Copy_ColumnNumber+0xC0);
				break;

			default:

				/* Function is not behaving as expected */
				Local_Status = RT_NOK;
		}
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status ;
}
