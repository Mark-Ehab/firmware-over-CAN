/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 *          Mark Ehab Tawfik (201)
 *          Hazem Mohamed Ezzeldin (1297)
 *          Azza Saeed Mohammed Gad (912)
 *          MennaTullah Ahmed Farrag Hefny (116)
 * \date: 12/9/2023
 * \brief: source file for FPEC
 ******************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						 ______ _____  ______ _____   _____                                                 */
/*						|  ____|  __ \|  ____/ ____| |  __ \                                                */
/*						| |__  | |__) | |__ | |      | |__) | __ ___   __ _ _ __ __ _ _ __ ___              */
/*						|  __| |  ___/|  __|| |      |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \             */
/*						| |    | |    | |___| |____  | |   | | | (_) | (_| | | | (_| | | | | | |            */
/*						|_|    |_|    |______\_____| |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|            */
/*						                                               __/ |                                */
/*						                            				  |___/                                 */
/*----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "standardTypes.h"
#include "common_macros.h"

#include "FPEC_Private.h"
#include "FPEC_Config.h"
#include "FPEC_Interface.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             FUNCTIONS IMPLEMENTATIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: FlashPageErase          					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_PageNumber				                          */
/*				   Brief: Number of page in flash to be erased					  */
/* 				   Range:(FPEC_PAGE_0 --> FPEC_PAGE_127) 						  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function erases a full page on flash memory based on its  */
/* 				   passed number									        	  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t FPEC_FlashPageErase(uint8_t Copy_PageNumber)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;				/* Variable to hold status of the function */

	/* Check if passed page number is within its valid range */
	if(Copy_PageNumber >= FPEC_PAGE_0 && Copy_PageNumber <= FPEC_PAGE_127)
	{
		/* Wait for Busy Flag */
		while (READ_BIT(FPEC->SR,SR_BSY) == 1);

		/* Check if FPEC is locked or not */
		if (READ_BIT(FPEC->CR,CR_LOCK) == 1)
		{
			/* Unlock FPEC */
			FPEC -> KEYR = FPEC_UNLOCK_KEY1;
			FPEC -> KEYR = FPEC_UNLOCK_KEY2;
		}

		/* Page Erase Operation */
		SET_BIT(FPEC->CR,CR_PER);

		/* Write page address to be erased */
		FPEC->AR = (uint32_t)(Copy_PageNumber * 1024) + FPEC_FLASH_FIRST_ADDRESS ;

		/* Start operation */
		SET_BIT(FPEC->CR,CR_STRT);

		/* Wait for Busy Flag */
		while (READ_BIT(FPEC->SR,SR_BSY) == 1);

		/* End of Page Erasing Operation */
		SET_BIT(FPEC->SR,SR_EOP);
		CLEAR_BIT(FPEC->CR,CR_PER);
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: EraseBankArea          					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_PageNumber				                          */
/*				   Brief: Number of bank start page in flash for the bank to be   */
/* 				          erased. 										  		  */
/*				   Range:(FPEC_PAGE_0 --> FPEC_PAGE_127)						  */
/*				   -------------------------------------------------------------- */
/*				   uint32_t Copy_BankSize								    	  */
/*				   Brief: Size of the bank to be erased in flash                  */
/*				   Range: Limited to flash size.                                  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function erases a full bank on flash memory based on	  */
/* 				   passed start page number	and bank size				       	  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t FPEC_EraseBankArea(uint8_t Copy_PageNumber , uint32_t Copy_BankSize)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;				/* Variable to hold status of the function */
	uint8_t Local_PageCounter;							/* Variable to hold counts of flash pages */

	/* Check if passed page number and bank size are within their valid ranges */
	if((Copy_PageNumber >= FPEC_PAGE_0 && Copy_PageNumber <= FPEC_PAGE_127) &&
	   (Copy_BankSize >= 0 && Copy_BankSize <= 4294967295))
	{
		/* Traverse over each page in the bank then erase it until you reach the bank end */
		for (Local_PageCounter = 0 ; Local_PageCounter < Copy_BankSize ; Local_PageCounter++)
		{
			/* Erase a page in flash memory */
			FPEC_FlashPageErase((uint8_t)(Local_PageCounter + Copy_PageNumber));
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
/* @Function Name: FlashWriteHexRecord	          					              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint32_t Copy_Address                                          */
/*				   Brief: Data Hex Record Address								  */
/*				   Range: Limited to flash size	(FPEC_FLASH_FIRST_ADDRESS -->	  */
/* 						  FPEC_FLASH_LASR_ADDRESS)								  */
/*				   -------------------------------------------------------------- */
/* 				   uint16_t* Copy_pData                                           */
/*				   Brief: Array of halfwords (Data Hex Record)					  */
/*				   Range: None								   					  */
/*				   -------------------------------------------------------------- */
/* 				   uint8_t Copy_Length				                      	      */
/*				   Brief: Halfword Count in Data Hex Record						  */
/*				   Range: Any value can be stored within one byte 				  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function writes a hex record on flash based on its		  */
/*				   passed address, data and length in halfwords					  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t FPEC_FlashWriteHexRecord(uint32_t Copy_Address, uint16_t* Copy_pData, uint8_t Copy_Length)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;				/* Variable to hold status of the function */
	uint8_t Local_HalfWordCounter;						/* Variable to hold counts of halfwords in data hex record */

	/* Check if passed pointer (array) is NULL pointer or not */
	if(Copy_pData != NULL)
	{
		/* Check if passed flash address and length are within their valid ranges */
		if((Copy_Address >= FPEC_FLASH_FIRST_ADDRESS && Copy_Address <= FPEC_FLASH_LAST_ADDRESS) &&
		   (Copy_Length >= 0 && Copy_Length <= 255))
		{
			/* Wait for Busy Flag */
			while (READ_BIT(FPEC->SR,SR_BSY) == 1);

			/* Check if FPEC is locked or not */
			if (READ_BIT(FPEC->CR,CR_LOCK) == 1)
			{
				/* Unlock FPEC */
				FPEC -> KEYR = FPEC_UNLOCK_KEY1;
				FPEC -> KEYR = FPEC_UNLOCK_KEY2;
			}

			for (Local_HalfWordCounter = 0; Local_HalfWordCounter < Copy_Length; Local_HalfWordCounter++)
			{
				/* Write Flash Programming */
				SET_BIT(FPEC->CR,CR_PG);

				/* Half word flash programming operation */
				*((volatile uint16_t*)Copy_Address) = Copy_pData[(uint32_t)Local_HalfWordCounter];
				Copy_Address += 2;

				/* Wait for Busy Flag */
				while (READ_BIT(FPEC->SR,SR_BSY) == 1);

				/* End of Flash Programming Operation */
				SET_BIT(FPEC->SR,SR_EOP);
				CLEAR_BIT(FPEC->CR,CR_PG);
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
		/* Passed pointer is NULL pointer */
		Local_Status = NULL_POINTER;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: WriteDataOptionByte          					              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_DataOptionByte                                    */
/* 				   Brief: Data Option Byte Id in which data will be stored        */
/*                 Range: (FPEC_DATA_OPTION_BYTE0 - FPEC_DATA_OPTION_BYTE1)	      */
/*                 -------------------------------------------------------------- */
/* 				   uint8_t Copy_Value				                   	          */
/*				   Brief: Value to be stored in Data option byte   				  */
/*				   Range: Any value can be stored within one byte				  */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function stores a value in selected Data option byte	  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t FPEC_WriteDataOptionByte(uint8_t Copy_DataOptionByte, uint8_t Copy_Value)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;				/* Variable to hold status of the function */

	/* Check if passed value and Data option byte Id are within there valid ranges */
	if ((Copy_DataOptionByte == FPEC_DATA_OPTION_BYTE0 || Copy_DataOptionByte == FPEC_DATA_OPTION_BYTE1) &&
		(Copy_Value >= 0 && Copy_Value <= 255))
	{
		/* Wait for Busy Flag */
		while (READ_BIT(FPEC->SR,SR_BSY) == 1);

		/* Check if FPEC is locked or not */
		if (READ_BIT(FPEC->CR,CR_LOCK) == 1)
		{
			/* Unlock FPEC */
			FPEC -> KEYR = FPEC_UNLOCK_KEY1;
			FPEC -> KEYR = FPEC_UNLOCK_KEY2;
		}

		/* Unlock Option Bytes Programming */
		FPEC -> OPTKEYR = FPEC_UNLOCK_KEY1;
		FPEC -> OPTKEYR = FPEC_UNLOCK_KEY2;

		/* Enable Option Bytes Programming */
		SET_BIT(FPEC->CR,CR_OPTWRE);

		/* Erase Option Bytes */
		SET_BIT(FPEC->CR,CR_OPTER);
		SET_BIT(FPEC->CR,CR_STRT);

		/* Wait for Busy Flag */
		while (READ_BIT(FPEC->SR,SR_BSY) == 1);

		/* End of Option Bytes Erase Operation */
		SET_BIT(FPEC->SR,SR_EOP);
		CLEAR_BIT(FPEC->CR,CR_OPTER);

		/* Program Option Bytes */
		SET_BIT(FPEC->CR,CR_OPTPG);

		/* Unlock read protection */
		*(volatile uint16_t*)(0x1FFFF800) = FPEC_READ_PROTECTION_UNLOCK_KEY;

		/* Wait for Busy Flag */
		while (READ_BIT(FPEC->SR,SR_BSY) == 1);

		/* Check passed option byte Id */
		if(Copy_DataOptionByte == FPEC_DATA_OPTION_BYTE0)
		{
			/* Set Data Option Byte0 */
			FPEC_DATA_OPTION_BYTE0_LOCATION = (uint16_t)Copy_Value;
		}
		else
		{
			/* Set Data Option Byte1 */
			FPEC_DATA_OPTION_BYTE1_LOCATION = (uint16_t)Copy_Value;
		}

		/* Wait for Busy Flag */
		while (READ_BIT(FPEC->SR,SR_BSY) == 1);

		/* End of Option Bytes Programming Operation */
		SET_BIT(FPEC->SR,SR_EOP);
		CLEAR_BIT(FPEC->CR,CR_OPTPG);
	}
	else
	{
		/* Function is not behaving as expected */
		Local_Status = RT_NOK;
	}

	return Local_Status;
}

/*--------------------------------------------------------------------------------*/
/* @Function Name: GetDataOptionByte	          					              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_DataOptionByte                                    */
/* 				   Brief: Data Option Byte Id which its value will be read        */
/*                 Range: (FPEC_DATA_OPTION_BYTE0 - FPEC_DATA_OPTION_BYTE1)	      */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : uint8_t* Copy_pValue                                           */
/*				   Brief: Input argument of type pointer to unit8_t that holds    */
/* 					   	  the address of the variable in which the data read from */
/*					  	  option byte Data0 will be stored						  */
/*				   Range: None													  */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t												  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function gets (reads) the value stored in option byte 	  */
/* 				   Data0	  													  */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t FPEC_GetDataOptionByte(uint8_t Copy_DataOptionByte, uint8_t* Copy_pValue)
{
	/* Local Variables Definitions */
	ERROR_STATUS_t Local_Status = RT_OK;				/* Variable to hold status of the function */

	/* Unlock read protection */
	*(volatile uint16_t*)(0x1FFFF800) = FPEC_READ_PROTECTION_UNLOCK_KEY;

	/* Wait for Busy Flag */
	while (READ_BIT(FPEC->SR,SR_BSY) == 1);

	/* Check if passed pointer is NULL pointer or not */
	if(Copy_pValue != NULL)
	{
		/* Switch on passed Data option byte Id */
		switch(Copy_DataOptionByte)
		{
		    case FPEC_DATA_OPTION_BYTE0:

				/* Get Value of Data Option Byte0 */
				*Copy_pValue = (uint8_t)((FPEC->OBR & FPEC_DATA_OPTION_BYTE0_MASK) >> 10);

				break;

		    case FPEC_DATA_OPTION_BYTE1:

				/* Get Value of Data Option Byte1 */
				*Copy_pValue = (uint8_t)((FPEC->OBR & FPEC_DATA_OPTION_BYTE1_MASK) >> 18);

				break;

		    default:

		    	/* Function is not behaving as expected */
		    	Local_Status = RT_NOK;
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
/* @Function Name: FlashMassErase          					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None                                                           */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function performs mass erase on flash memory  			  */
/*--------------------------------------------------------------------------------*/
void FPEC_FlashMassErase(void)
{
	/* Wait for Busy Flag */
	while (READ_BIT(FPEC->SR,SR_BSY) == 1);

	/* Check if FPEC is locked or not */
	if (READ_BIT(FPEC->CR,CR_LOCK) == 1)
	{
		FPEC -> KEYR = FPEC_UNLOCK_KEY1;
		FPEC -> KEYR = FPEC_UNLOCK_KEY2;
	}

	/* Mass Erase Operation */
	SET_BIT(FPEC->CR,CR_MER);

	/* Start operation */
	SET_BIT(FPEC->CR,CR_STRT);

	/* Wait for Busy Flag */
	while (READ_BIT(FPEC->SR,SR_BSY) == 1);

	/* End of Page Erasing Operation */
	SET_BIT(FPEC->SR,SR_EOP);
	CLEAR_BIT(FPEC->CR,CR_MER);
}



/*--------------------------------------------------------------------------------*/
/* @Function Name: FPEC_erasePagesFromTo          					              */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t startPageNumber , uint8_t EndPageNumber                */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : ERROR_STATUS_t                                          		  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : This function erases pages from the passed start page to the   */
/*                 passed endPage                                  			      */
/*--------------------------------------------------------------------------------*/
ERROR_STATUS_t FPEC_erasePagesFromTo(uint8_t startPageNumber , uint8_t EndPageNumber){
	uint8_t pageNumber;
	ERROR_STATUS_t status = RT_OK;
	/* checking if the passed startPageNumber and EndPageNumber fit the FLASH size */
	if( startPageNumber >= FLASH_FIRST_PAGE_NUM && EndPageNumber <= FLASH_LAST_PAGE_NUM){
		/* loop over the desired pages to be erased. */
		for(pageNumber = startPageNumber; pageNumber< EndPageNumber ; pageNumber++){
			FPEC_FlashPageErase(pageNumber);
		}
	} else{
		status = RT_NOK;
	}
	return status;
}
