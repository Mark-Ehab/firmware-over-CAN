/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 *          Mark Ehab Tawfik (201)
 *          Hazem Mohamed Ezzeldin (1297)
 *          Azza Saeed Mohammed Gad (912)
 *          MennaTullah Ahmed Farrag Hefny (116)
 * \date: 12/9/2023
 * \brief: private header file for FPEC
 ******************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*		                     ______ _____  ______ _____   _____      _            _                         */
/*		                    |  ____|  __ \|  ____/ ____| |  __ \    (_)          | |                        */
/*		                    | |__  | |__) | |__ | |      | |__) | __ ___   ____ _| |_ ___                   */
/*		                    |  __| |  ___/|  __|| |      |  ___/ '__| \ \ / / _` | __/ _ \                  */
/*		                    | |    | |    | |___| |____  | |   | |  | |\ V / (_| | ||  __/                  */
/*		                    |_|    |_|    |_____ \_____| |_|   |_|  |_| \_/ \__,_|\__\___|                  */
/*							                                                  							    */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef FPEC_MCAL_PRIVATE_H_
#define FPEC_MCAL_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            	 FPEC REGISTERS DEFINITION		          		     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
typedef struct
{
	volatile uint32_t ACR;              /* Flash access control register */
	volatile uint32_t KEYR;             /* FPEC key register */
	volatile uint32_t OPTKEYR;          /* Flash OPTKEY register */
	volatile uint32_t SR;               /* Flash status register */
	volatile uint32_t CR;               /* Flash control register */
	volatile uint32_t AR;               /* Flash address register */
	volatile uint32_t RESERVED;         /* Reserved Bits */
	volatile uint32_t OBR;              /* Option byte register  */
	volatile uint32_t WRPR;             /* Write protection register */
}FPEC_t;

#define FPEC ((volatile FPEC_t*)0x40022000)

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              SOME BITS DEFINITIONS		 	             		 */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
/* Some bit definitions of Flash control register (FLASH_CR) */
#define CR_PG					0U
#define CR_PER                  1U
#define CR_MER                  2U
#define CR_OPTPG                4U
#define CR_OPTER                5U
#define CR_STRT                 6U
#define CR_LOCK                 7U
#define CR_OPTWRE               9U
#define CR_ERRIE                10U
#define CR_EOPIE                12U

/* Some bit definitions of Flash status register (FLASH_SR) */
#define SR_BSY					0U
#define SR_PGERR                2U
#define SR_WRPRTERR             4U
#define SR_EOP                  5U

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            		PRIVATE MACROS				       		         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
/* Flash Memory Unlock Keys */
#define FPEC_UNLOCK_KEY1					0x45670123U
#define FPEC_UNLOCK_KEY2                    0xCDEF89ABU
#define FPEC_READ_PROTECTION_UNLOCK_KEY		0x00A5U

/* Flash Option Bytes Location Addresses */
#define FPEC_DATA_OPTION_BYTE0_LOCATION 	*(volatile uint16_t*)(0x1FFFF804)
#define FPEC_DATA_OPTION_BYTE1_LOCATION 	*(volatile uint16_t*)(0x1FFFF806)

/* Data Option Bytes Masks */
#define FPEC_DATA_OPTION_BYTE0_MASK 		0x0003FC00U
#define FPEC_DATA_OPTION_BYTE1_MASK 		0x03FC0000U

/* flash pages boundaries */
#define FLASH_FIRST_PAGE_NUM                0
#define FLASH_LAST_PAGE_NUM                 127

#endif /* FPEC_MCAL_PRIVATE_H_ */
