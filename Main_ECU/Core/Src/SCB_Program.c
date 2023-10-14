/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 *          Mark Ehab Tawfik (201)
 *          Hazem Mohamed Ezzeldin (1297)
 *          Azza Saeed Mohammed Gad (912)
 *          MennaTullah Ahmed Farrag Hefny (116)
 * \date: 25/9/2023
 * \brief: source file of the SCB
 ******************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						  _____  _____ ____    _____                                                        */
/*						 / ____|/ ____|  _ \  |  __ \                                                       */
/*						| (___ | |    | |_) | | |__) | __ ___   __ _ _ __ __ _ _ __ ___                     */
/*						 \___ \| |    |  _ <  |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \                    */
/*						 ____) | |____| |_) | | |   | | | (_) | (_| | | | (_| | | | | | |                   */
/*						|_____/ \_____|____/  |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|                   */
/*						                                        __/ |                                       */
/*						                     					|___/                                       */
/*----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "../Inc/standardTypes.h"
#include "../Inc/common_macros.h"

#include "../Inc/SCB_Private.h"
#include "../Inc/SCB_Config.h"
#include "../Inc/SCB_Interface.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             FUNCTIONS IMPLEMENTATIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: ShiftInterruptVectorTable          					          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_InterruptProirityGroup					          */
/*				   Brief: Specify the group priority and the sub priority of each */
/*					      interrupt 											  */
/*				   Range: (SCB_INT_PRIGROUP_G16S0 -> SCB_INT_PRIGROUP_G0S16) 	  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                     			  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function sets the grouping priority of each interrupt     */
/*				   through setting its group and sub priorities                   */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t SCB_SetInterruptPriorityGroup(uint8_t Copy_InterruptProirityGroup)
{
	/* Local Variables Definitions */
	uint8_t Local_Status = RT_OK;

	/* Check if passed interrupt priority group is valid or not */
	if(Copy_InterruptProirityGroup == SCB_INT_PRIGROUP_G0S16 ||
	   Copy_InterruptProirityGroup == SCB_INT_PRIGROUP_G2S8  ||
	   Copy_InterruptProirityGroup == SCB_INT_PRIGROUP_G4S4  ||
	   Copy_InterruptProirityGroup == SCB_INT_PRIGROUP_G8S2  ||
	   Copy_InterruptProirityGroup == SCB_INT_PRIGROUP_G16S0)
	{
		/* Clear PRIGROUP Bits in AIRCR Register */
		SCB->AIRCR &= SCB_INTERRUPT_PRIGROUP_MASK;

		/* Set Priority Grouping in  AIRCR Register*/
		SCB->AIRCR |= (Copy_InterruptProirityGroup << 8);
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: ShiftInterruptVectorTable          					          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint32_t Copy_VectorTableOffset				                  */
/*				   Brief: The offset required to shift the interrupt vector table */
/*				          from interrupt vector table base (0x00000000)			  */
/*				   Range: (0x00000000 --> 0x3FFFFE00)							  */
/*				   Note : Vector table offset must be aligned to the number of    */
/*						  exception entries in the vector table. The minimum      */
/*						  alignment is 128 words. Table alignment requirements    */
/*						  mean that bits[8:0] of the table offset are always zero.*/
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                     			  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function is intended to force a large system software	  */
/* 				   reset of all major components								  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t SCB_ShiftInterruptVectorTable(uint32_t Copy_VectorTableOffset)
{
	/* Local Variables Definitions */
	uint8_t Local_Status = RT_OK;

	/* Check if passed vector table offset is within the valid range */
	if((Copy_VectorTableOffset >= 0x00000000 && Copy_VectorTableOffset <= 0x3FFFFE00) &&
	   ((Copy_VectorTableOffset & 0x000000FF) == 0))
	{
		SCB->VTOR = Copy_VectorTableOffset;
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}
	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: SCB_PerformSoftReset          					              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function is intended to force a large system software	  */
/* 				   reset of all major components								  */
/*--------------------------------------------------------------------------------*/
void SCB_PerformSoftReset(void)
{
	/* Perform soft reset through setting SYSRESETREQ in AIRCR Register */
	SET_BIT(SCB->AIRCR,AIRCR_SYSRESETREQ);
}
