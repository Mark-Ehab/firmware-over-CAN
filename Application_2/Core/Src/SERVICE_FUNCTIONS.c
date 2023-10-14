/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Jan 17, 2022               	*/
/*            	    Description	 : Service Functions Program    */
/* 	        	    Version      : V1.0                         */
/****************************************************************/

/*---------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                         					 */
/*		  _____ ______ _______      _______ _____ ______   ______ _    _ _   _  _____ _______ _____ ____  _   _  _____       */
/*		 / ____|  ____|  __ \ \    / /_   _/ ____|  ____| |  ____| |  | | \ | |/ ____|__   __|_   _/ __ \| \ | |/ ____|      */
/*		| (___ | |__  | |__) \ \  / /  | || |    | |__    | |__  | |  | |  \| | |       | |    | || |  | |  \| | (___        */
/*		 \___ \|  __| |  _  / \ \/ /   | || |    |  __|   |  __| | |  | | . ` | |       | |    | || |  | | . ` |\___ \       */
/*		 ____) | |____| | \ \  \  /   _| || |____| |____  | |    | |__| | |\  | |____   | |   _| || |__| | |\  |____) |      */
/*		|_____/|______|_|  \_\  \/   |_____\_____|______| |_|     \____/|_| \_|\_____|  |_|  |_____\____/|_| \_|_____/       */
/*				                                                                                                   			 */
/*						                                                                                   					 */
/*---------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 	 LIBRARIES		       		            	     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "../Inc/standardTypes.h"
#include "../Inc/SERVICE_FUNCTIONS.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             FUNCTIONS IMPLEMENTATIONS		                   	 */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name 	: CeilDev										        	  */
/*--------------------------------------------------------------------------------*/
/* @Param(in) 		: sint32_t Copy_InputMin  									  */
/* 					  sint32_t Copy_InputMax		      						  */
/*					  sint32_t Copy_OutputMin                                     */
/*					  sint32_t Copy_OutputMax                                     */
/*					  sint32_t Copy_InputVal                                      */
/*--------------------------------------------------------------------------------*/
/* @Param(inout)	: None														  */
/*--------------------------------------------------------------------------------*/
/* @Param(out)		: None														  */
/*--------------------------------------------------------------------------------*/
/* @Return          : sint32_t    	        	      		        			  */
/*--------------------------------------------------------------------------------*/
/* @Description     : This function is used to map a value in some input range to */
/*					  its equivalent value in output range				    	  */
/*--------------------------------------------------------------------------------*/
sint32_t SERV_Map(sint32_t Copy_InputMin  , sint32_t Copy_InputMax,
			      sint32_t Copy_OutputMin , sint32_t Copy_OutputMax,
			      sint32_t Copy_InputVal )
{
		/* Local Variables Definitions */
		sint32_t  Local_MappingResult; 		/* Holds the mapping result */
		float32_t Local_Slope = (float32_t)(Copy_OutputMax - Copy_OutputMin)/(float32_t)(Copy_InputMax - Copy_InputMin); /* Slope */

		/* Get Mapping Result From the Following Straight-Line Equation */
		Local_MappingResult = (Local_Slope * (float32_t)Copy_InputVal) - (Local_Slope * (float32_t)Copy_InputMin) + (float32_t)Copy_OutputMin;

		return Local_MappingResult;
}
/*--------------------------------------------------------------------------------*/
/* @Function Name 	: Mod   										        	  */
/*--------------------------------------------------------------------------------*/
/* @Param(in) 		: float32_t Copy_Num1  										  */
/* 					  float32_t Copy_Num2		      						  	  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout)	: None														  */
/*--------------------------------------------------------------------------------*/
/* @Param(out)		: None														  */
/*--------------------------------------------------------------------------------*/
/* @Return          : float32_t  	        	      		        			  */
/*--------------------------------------------------------------------------------*/
/* @Description     : Function to get modulus of two numbers					  */
/*--------------------------------------------------------------------------------*/
float32_t SERV_Mod(float32_t Copy_Num1 , float32_t Copy_Num2)
{
		/* Local Variables Definitions */
		float32_t Local_Result;  			 	/* A variable to hold the result */

		/* Calculate the modulus */
	        Local_Result = Copy_Num1 - ((uint32_t)(Copy_Num1/Copy_Num2) * Copy_Num2);

		return Local_Result;
}
/*--------------------------------------------------------------------------------*/
/* @Function Name 	: CeilDev										        	  */
/*--------------------------------------------------------------------------------*/
/* @Param(in) 		: float32_t Copy_Num1  										  */
/* 					  float32_t Copy_Num2		      						  	  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout)	: None														  */
/*--------------------------------------------------------------------------------*/
/* @Param(out)		: None														  */
/*--------------------------------------------------------------------------------*/
/* @Return          : uint32_t  	        	      		        			  */
/*--------------------------------------------------------------------------------*/
/* @Description     : Function to get ceil of the result of two dividend numbers  */
/*--------------------------------------------------------------------------------*/
uint32_t SERV_CeilDev(float32_t Copy_Num1 , float32_t Copy_Num2)
{
	/* Local Variables Definitions */
	uint32_t Local_Result;				/* A variable to hold result after ceiling */

	/* Calculate result then ceil it */
	Local_Result = (uint32_t)(Copy_Num1/Copy_Num2) + (SERV_Mod(Copy_Num1,Copy_Num2)!= 0);

	return Local_Result;
}
/*--------------------------------------------------------------------------------*/
/* @Function Name 	: Pow											        	  */
/*--------------------------------------------------------------------------------*/
/* @Param(in) 		: uint32_t Copy_Base 										  */
/* 					  uint32_t Copy_Power		      						  	  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout)	: None														  */
/*--------------------------------------------------------------------------------*/
/* @Param(out)		: None														  */
/*--------------------------------------------------------------------------------*/
/* @Return          : uint32_t  	        	      		        			  */
/*--------------------------------------------------------------------------------*/
/* @Description     : Function to get the power of a number		       		      */
/*--------------------------------------------------------------------------------*/
uint32_t SERV_Pow(uint32_t Copy_Base , uint32_t Copy_Power)
{
	/* Local Variables Definitions */
	uint32_t Local_Result ;              	/* A variable to hold result of power process of passed number */

	/* Initialize Local_u32Result to be equal to 1 */
	Local_Result = 1;

	/* Check if passed power value equal 0 or not */
	if(Copy_Power != 0)
	{
		/* Calculate the power of passed number */
		while(Copy_Power != 0)
		{
		    /* Decrease power value */
		    Copy_Power --;

		    /* Get the result */
		    Local_Result *= Copy_Base;
		}
	}

	return Local_Result;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name 	: Pow											        	  */
/*--------------------------------------------------------------------------------*/
/* @Param(in) 		: uint32_t Copy_Time										  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout)	: None														  */
/*--------------------------------------------------------------------------------*/
/* @Param(out)		: None														  */
/*--------------------------------------------------------------------------------*/
/* @Return          : uint32_t  	        	      		        			  */
/*--------------------------------------------------------------------------------*/
/* @Description     : Function to block the processor for specified delay in ms	  */
/*--------------------------------------------------------------------------------*/
uint32_t SERV_Delay_ms(uint32_t Copy_Time)
{
	uint32_t Local_Ticks = (500 * Copy_Time);
	uint32_t Local_TicksCounter;

	for(Local_TicksCounter = 0 ; Local_TicksCounter < Local_Ticks ;Local_TicksCounter++)
	{
		__asm("NOP");
	}
	return Local_TicksCounter;
}
