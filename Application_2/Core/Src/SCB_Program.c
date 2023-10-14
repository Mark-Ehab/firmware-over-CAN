/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 25, 2023               	*/
/*      			SWC          : SCB  			            */
/*     			    Description	 : SCB Program                  */
/* 	   				Version      : V1.0                         */
/****************************************************************/

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
#include "STD_TYPES.h"
#include "STD_ERRORS.h"
#include "BIT_MATH.h"

#include "SCB_Private.h"
#include "SCB_Config.h"
#include "SCB_Interface.h"

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
	uint32_t Local_AIRCR_RegisterClone;			/* Variable to hold clone value of AIRCR register*/

	/* Check if passed interrupt priority group is valid or not */
	if(Copy_InterruptProirityGroup == SCB_INT_PRIGROUP_G0S16 || Copy_InterruptProirityGroup == SCB_INT_PRIGROUP_G2S8  ||
	   Copy_InterruptProirityGroup == SCB_INT_PRIGROUP_G4S4  || Copy_InterruptProirityGroup == SCB_INT_PRIGROUP_G8S2  ||
	   Copy_InterruptProirityGroup == SCB_INT_PRIGROUP_G16S0)
	{
		/* Assign AIRCR register current value to Local_AIRCR_RegisterClone variable */
		Local_AIRCR_RegisterClone = SCB->AIRCR;

		/* Mask bits [16:31] of AIRCR Register Key in Local_AIRCR_RegisterClone variable */
		Local_AIRCR_RegisterClone &= SCB_VECTKEY_MASK;

		/* Write AIRCR Register Key in Local_AIRCR_RegisterClone variable in bits [16:31] to be able to write on register */
		Local_AIRCR_RegisterClone |= SCB_VECTKEY;

		/* Clear PRIGROUP Bits in Local_AIRCR_RegisterClone variable */
		Local_AIRCR_RegisterClone &= SCB_INTERRUPT_PRIGROUP_MASK;

		/* Set Priority Grouping in Local_AIRCR_RegisterClone variable */
		Local_AIRCR_RegisterClone |= (Copy_InterruptProirityGroup << 8);

		/* Assign the last value of Local_AIRCR_RegisterClone variable after modification to AIRCR register */
		SCB->AIRCR = Local_AIRCR_RegisterClone;
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
/* @Description	 : This function is intended to shift static interrupt vector  	  */
/*                 table by hardware based on passed offset to desired place in   */
/*                 flash memory in which interrupt vector table must be aligned   */
/*                 in at least 128 words		 								  */
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
	/* Local Variables Definitions */
	uint32_t Local_AIRCR_RegisterClone;			/* Variable to hold clone value of AIRCR register*/

	/* Assign AIRCR register current value to Local_AIRCR_RegisterClone variable */
	Local_AIRCR_RegisterClone = SCB->AIRCR;

	/* Mask bits [16:31] of AIRCR Register Key in Local_AIRCR_RegisterClone variable */
	Local_AIRCR_RegisterClone &= SCB_VECTKEY_MASK;

	/* Write AIRCR Register Key in Local_AIRCR_RegisterClone variable in bits [16:31] to be able to write on register */
	Local_AIRCR_RegisterClone |= SCB_VECTKEY;

	/* Perform soft reset through setting SYSRESETREQ bit (Bit 2) in Local_AIRCR_RegisterClone variable */
	SET_BIT(Local_AIRCR_RegisterClone,AIRCR_SYSRESETREQ);

	/* Assign the last value of Local_AIRCR_RegisterClone variable after modification to AIRCR register */
	SCB->AIRCR = Local_AIRCR_RegisterClone;
}
