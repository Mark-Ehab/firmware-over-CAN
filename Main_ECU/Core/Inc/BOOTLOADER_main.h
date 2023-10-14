/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 *          Mark Ehab Tawfik (201)
 *          Hazem Mohamed Ezzeldin (1297)
 *          Azza Saeed Mohammed Gad (912)
 *          MennaTullah Ahmed Farrag Hefny (116)
 * \date: 9/10/2023
 * \brief: header file for the BOOTLOADER_main
 ******************************************************/

#ifndef INC_BOOTLOADER_MAIN_H_
#define INC_BOOTLOADER_MAIN_H_

/* defining the character of the end of the record */
#define APP_END_OF_RECORD               '\n'

/* maximum elements of the record */
#define APP_BUFFER_MAX_ELEMENTS         100

/* SysTick time out value */
#define APP_TIME_OUT_VAL                15

/* time out flag */
#define APP_TIMEOUT_FLAG_NOT_SET        0
#define APP_TIMEOUT_FLAG_SET            1

/* upper part of the first and second applications */
#define APP_BANK_1_ADDRESS_UPPER_PART    0x08000000
#define APP_BANK_2_ADDRESS_UPPER_PART    0x08010000

/* addresses of the vector table and the reset handler of APP1 and APP2 */
#define APP_1_VECTOR_TABLE_ADDRESS       0x08008000
#define APP_1_RESET_HANDLER_ADDRESS      0x08008004
#define APP_2_VECTOR_TABLE_ADDRESS       0x08010000
#define APP_2_RESET_HANDLER_ADDRESS      0x08010004

/* page number of the beginning of APP1 and APP2 */
#define APP_1_PAGE_NUM                   32
#define APP_2_PAGE_NUM                   64

/* size of APP1 and APP2 */
#define APP_1_SIZE                       32
#define APP_2_SIZE                       32

/* flags of APP1 and APP2 that are in the option byte DATA0 */
#define APP_1_BANK_FLAG                  BANK1_FLAG
#define APP_2_BANK_FLAG                  BANK2_FLAG

/* Ids of the 2 applications */
typedef enum{
	APP_1_ID = 1,
	APP_2_ID
} APPs_ID;

/* if the APP isn't completely flashed yet */
#define APP_FLASH_NOT_COMPLETE           'n'

#endif /* INC_BOOTLOADER_MAIN_H_ */
