/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 *          Mark Ehab Tawfik (201)
 *          Hazem Mohamed Ezzeldin (1297)
 *          Azza Saeed Mohammed Gad (912)
 *          MennaTullah Ahmed Farrag Hefny (116)
 * \date: 12/9/2023
 * \brief: interface header file for FPEC
 ******************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*						 ______ _____  ______ _____   _____       _             __                          */
/*						|  ____|  __ \|  ____/ ____| |_   _|     | |           / _|                         */
/*						| |__  | |__) | |__ | |        | |  _ __ | |_ ___ _ __| |_ __ _  ___ ___            */
/*						|  __| |  ___/|  __|| |        | | | '_ \| __/ _ \ '__|  _/ _` |/ __/ _ \           */
/*						| |    | |    | |___| |____   _| |_| | | | ||  __/ |  | || (_| | (_|  __/           */
/*						|_|    |_|    |______\_____| |_____|_| |_|\__\___|_|  |_| \__,_|\___\___|           */
/*						                                                                                    */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef FPEC_MCAL_INTERFACE_H_
#define FPEC_MCAL_INTERFACE_H_

#include "standardTypes.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	    INTERFACE MACROS		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Range of Flash Memory Pages (In STM32F103XXXX Medium Density Controllers Family)*/
#define FPEC_PAGE_0                            0U
#define FPEC_PAGE_1                            1U
#define FPEC_PAGE_2                            2U
#define FPEC_PAGE_3                            3U
#define FPEC_PAGE_4                            4U
#define FPEC_PAGE_5                            5U
#define FPEC_PAGE_6                            6U
#define FPEC_PAGE_7                            7U
#define FPEC_PAGE_8                            8U
#define FPEC_PAGE_9                            9U
#define FPEC_PAGE_10                           10U
#define FPEC_PAGE_11                           11U
#define FPEC_PAGE_12                           12U
#define FPEC_PAGE_13                           13U
#define FPEC_PAGE_14                           14U
#define FPEC_PAGE_15                           15U
#define FPEC_PAGE_16                           16U
#define FPEC_PAGE_17                           17U
#define FPEC_PAGE_18                           18U
#define FPEC_PAGE_19                           19U
#define FPEC_PAGE_20                           20U
#define FPEC_PAGE_21                           21U
#define FPEC_PAGE_22                           22U
#define FPEC_PAGE_23                           23U
#define FPEC_PAGE_24                           24U
#define FPEC_PAGE_25                           25U
#define FPEC_PAGE_26                           26U
#define FPEC_PAGE_27                           27U
#define FPEC_PAGE_28                           28U
#define FPEC_PAGE_29                           29U
#define FPEC_PAGE_30                           30U
#define FPEC_PAGE_31                           31U
#define FPEC_PAGE_32                           32U
#define FPEC_PAGE_33                           33U
#define FPEC_PAGE_34                           34U
#define FPEC_PAGE_35                           35U
#define FPEC_PAGE_36                           36U
#define FPEC_PAGE_37                           37U
#define FPEC_PAGE_38                           38U
#define FPEC_PAGE_39                           39U
#define FPEC_PAGE_40                           40U
#define FPEC_PAGE_41                           41U
#define FPEC_PAGE_42                           42U
#define FPEC_PAGE_43                           43U
#define FPEC_PAGE_44                           44U
#define FPEC_PAGE_45                           45U
#define FPEC_PAGE_46                           46U
#define FPEC_PAGE_47                           47U
#define FPEC_PAGE_48                           48U
#define FPEC_PAGE_49                           49U
#define FPEC_PAGE_50                           50U
#define FPEC_PAGE_51                           51U
#define FPEC_PAGE_52                           52U
#define FPEC_PAGE_53                           53U
#define FPEC_PAGE_54                           54U
#define FPEC_PAGE_55                           55U
#define FPEC_PAGE_56                           56U
#define FPEC_PAGE_57                           57U
#define FPEC_PAGE_58                           58U
#define FPEC_PAGE_59                           59U
#define FPEC_PAGE_60                           60U
#define FPEC_PAGE_61                           61U
#define FPEC_PAGE_62                           62U
#define FPEC_PAGE_63                           63U
#define FPEC_PAGE_64                           64U
#define FPEC_PAGE_65                           65U
#define FPEC_PAGE_66                           66U
#define FPEC_PAGE_67                           67U
#define FPEC_PAGE_68                           68U
#define FPEC_PAGE_69                           69U
#define FPEC_PAGE_70                           70U
#define FPEC_PAGE_71                           71U
#define FPEC_PAGE_72                           72U
#define FPEC_PAGE_73                           73U
#define FPEC_PAGE_74                           74U
#define FPEC_PAGE_75                           75U
#define FPEC_PAGE_76                           76U
#define FPEC_PAGE_77                           77U
#define FPEC_PAGE_78                           78U
#define FPEC_PAGE_79                           79U
#define FPEC_PAGE_80                           80U
#define FPEC_PAGE_81                           81U
#define FPEC_PAGE_82                           82U
#define FPEC_PAGE_83                           83U
#define FPEC_PAGE_84                           84U
#define FPEC_PAGE_85                           85U
#define FPEC_PAGE_86                           86U
#define FPEC_PAGE_87                           87U
#define FPEC_PAGE_88                           88U
#define FPEC_PAGE_89                           89U
#define FPEC_PAGE_90                           90U
#define FPEC_PAGE_91                           91U
#define FPEC_PAGE_92                           92U
#define FPEC_PAGE_93                           93U
#define FPEC_PAGE_94                           94U
#define FPEC_PAGE_95                           95U
#define FPEC_PAGE_96                           96U
#define FPEC_PAGE_97                           97U
#define FPEC_PAGE_98                           98U
#define FPEC_PAGE_99                           99U
#define FPEC_PAGE_100                          100U
#define FPEC_PAGE_101                          101U
#define FPEC_PAGE_102                          102U
#define FPEC_PAGE_103                          103U
#define FPEC_PAGE_104                          104U
#define FPEC_PAGE_105                          105U
#define FPEC_PAGE_106                          106U
#define FPEC_PAGE_107                          107U
#define FPEC_PAGE_108                          108U
#define FPEC_PAGE_109                          109U
#define FPEC_PAGE_110                          110U
#define FPEC_PAGE_111                          111U
#define FPEC_PAGE_112                          112U
#define FPEC_PAGE_113                          113U
#define FPEC_PAGE_114                          114U
#define FPEC_PAGE_115                          115U
#define FPEC_PAGE_116                          116U
#define FPEC_PAGE_117                          117U
#define FPEC_PAGE_118                          118U
#define FPEC_PAGE_119                          119U
#define FPEC_PAGE_120                          120U
#define FPEC_PAGE_121                          121U
#define FPEC_PAGE_122                          122U
#define FPEC_PAGE_123                          123U
#define FPEC_PAGE_124                          124U
#define FPEC_PAGE_125                          125U
#define FPEC_PAGE_126                          126U
#define FPEC_PAGE_127                          127U

/* Important Flash Addresses */
#define FPEC_FLASH_FIRST_ADDRESS			   0x08000000U
#define FPEC_FLASH_LAST_ADDRESS				   0x0801FFFFU

/* Data Option Byte Options */
#define FPEC_DATA_OPTION_BYTE0				   0U
#define FPEC_DATA_OPTION_BYTE1                 1U

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  FUNCTIONS PROTOTYPES		          	             */
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
ERROR_STATUS_t FPEC_FlashPageErase(uint8_t Copy_PageNumber);

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
ERROR_STATUS_t FPEC_EraseBankArea(uint8_t Copy_PageNumber , uint32_t Copy_BankSize);

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
ERROR_STATUS_t FPEC_FlashWriteHexRecord(uint32_t Copy_Address, uint16_t* Copy_pData, uint8_t Copy_Length);

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
ERROR_STATUS_t FPEC_WriteDataOptionByte(uint8_t Copy_DataOptionByte, uint8_t Copy_Value);

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
ERROR_STATUS_t FPEC_GetDataOptionByte(uint8_t Copy_DataOptionByte, uint8_t* Copy_pValue);

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
void FPEC_FlashMassErase(void);


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
ERROR_STATUS_t FPEC_erasePagesFromTo(uint8_t startPageNumber , uint8_t EndPageNumber);

#endif /* FPEC_MCAL_INTERFACE_H_ */
