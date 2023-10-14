/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 25, 2023               	*/
/*      			SWC          : SCB  			            */
/*     			    Description	 : SCB Interface                */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						  _____  _____ ____    _____       _             __                                 */
/*						 / ____|/ ____|  _ \  |_   _|     | |           / _|                                */
/*						| (___ | |    | |_) |   | |  _ __ | |_ ___ _ __| |_ __ _  ___ ___                   */
/*						 \___ \| |    |  _ <    | | | '_ \| __/ _ \ '__|  _/ _` |/ __/ _ \                  */
/*						 ____) | |____| |_) |  _| |_| | | | ||  __/ |  | || (_| | (_|  __/                  */
/*						|_____/ \_____|____/  |_____|_| |_|\__\___|_|  |_| \__,_|\___\___|                  */
/*						                                                                                    */
/*                                                                                                	        */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef SCB_MCAL_INTERFACE_H_
#define SCB_MCAL_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	    INTERFACE MACROS		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Interrupt Priority Group Options */
#define SCB_INT_PRIGROUP_G16S0	0b011
#define SCB_INT_PRIGROUP_G8S2   0b100
#define SCB_INT_PRIGROUP_G4S4   0b101
#define SCB_INT_PRIGROUP_G2S8   0b110
#define SCB_INT_PRIGROUP_G0S16  0b111


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  FUNCTIONS PROTOTYPES		          	             */
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
ERROR_STATUS_t SCB_SetInterruptPriorityGroup(uint8_t Copy_InterruptProirityGroup);

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
ERROR_STATUS_t SCB_ShiftInterruptVectorTable(uint32_t Copy_VectorTableOffset);

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
void SCB_PerformSoftReset(void);

#endif /* SCB_MCAL_INTERFACE_H_ */
