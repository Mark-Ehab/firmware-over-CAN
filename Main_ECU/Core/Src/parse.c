/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 *          Mark Ehab Tawfik (201)
 *          Hazem Mohamed Ezzeldin (1297)
 *          Azza Saeed Mohammed Gad (912)
 *          MennaTullah Ahmed Farrag Hefny (116)
 * \date: 9/10/2023
 * \brief: source file to parse a .hex and save
 *              it in the FLASH
 ******************************************************/


/* including some files*/
#include "../Inc/standardTypes.h"
#include "../Inc/common_macros.h"
#include "../Inc/FPEC_Interface.h"
#include "../Inc/FPEC_Config.h"
#include "../Inc/BOOTLOADER_main.h"
#include "../Inc/parse.h"

/* Global variables */

/* Global variable to hold the address */
uint32_t address;
/* Global variable to current application */
uint8_t currentApp = NULL;

/************************************************************************
 * Service name: ASCII_TO_HEX
 *
 * Parameters in: uint8_t ASCII_data
 *               (the ASCII value that needed to be converted to hex)
 *
 * Parameters in/out: None
 *
 * Parameters out: None
 *
 * Return: uint8_t HexData (value after conversion)
 *
 * Description: this function is responsible of converting the passed
 *              ASCII value to hex.
 ************************************************************************/
uint8_t ASCII_TO_HEX(uint8_t ASCII_data){
	/* Local variable to hold the converted value*/
	uint8_t HexData;

	/* checking if the passed value if from A to F or from 0 to 9*/
	if(ASCII_data >= 'A' && ASCII_data <='F'){

		/* if the passed value is from A to F then subtracting 0x0A    *
		 * to get the corresponding hex value for example:             *
		 * 'A' is passed which is 65 and we want the corresponding     *
		 * value which is 10 or 0x0A, so, 'A' - 0x0A = 65 - 10 == 55   *
		 * which means to get the corresponding value for any passed   *
		 * ASCII character is to subtract 55 from it.                  *
		 * 0xB = 11 & 'B' = 66 ---> 'B' - ('A' - 0x0A) = 66 - 55 = 11  *
		 * where 11 is 0xB                                             */

		HexData = ASCII_data - ('A' - 0x0A);
	}
	/* if the passed value is from 0 to 9 */
	else if(ASCII_data >= '0' && ASCII_data <='9'){
		/* subtracting '0' from the passed ASCII character */
		HexData = ASCII_data - ('0');
	}
	/* if the passed value is out of range */
	else{
		/* error handling */
	}
	return HexData;
}

/************************************************************************
 * Service name: parseAddressUpperPart
 *
 * Parameters in: uint8_t * record
 *               (the record to be parsed to extract the upper part
 *                of the address)
 *
 * Parameters in/out: None
 *
 * Parameters out: None
 *
 * Return: void
 *
 * Description: this function is responsible of extracting the upper
 *              part of the address.
 ************************************************************************/
void parseAddressUpperPart(uint8_t * record){
/* Local variables: */
	/* Local variable to hold the upper part of the address */
	uint16_t AdressUpperPart = 0;

	/* Local variable to hold the digits of the             *
	 * upper part of the address after converting it.       */
	uint8_t digits[4] = {0};

/* Address upper part */
	/* converting each digit from ASCII to the corresponding *
	 * hex value.                                            */
	digits[0] = ASCII_TO_HEX(record[9]);
	digits[1] = ASCII_TO_HEX(record[10]);
	digits[2] = ASCII_TO_HEX(record[11]);
	digits[3] = ASCII_TO_HEX(record[12]);

	/* Assigning the AdressUpperPart variable with the digits after  *
	 * converting them.                                              */
	AdressUpperPart = (digits[0]<<4*3) |
			          (digits[1]<<4*2) |
					  (digits[2]<<4) |
					  (digits[3]);

	/* shifting the upper part to be put in its right place in the address  *
	 * address = 0xyyyyyyyy                                                 *
	 *             |||| -> upper part of the address                        */
	address = AdressUpperPart << 4*4;
}


/************************************************************************
 * Service name: parseData
 *
 * Parameters in: uint8_t* record
 *               (the record to be parsed to extract the data
 *                to flash it in the memory)
 *
 * Parameters in/out: None
 *
 * Parameters out: None
 *
 * Return: void
 *
 * Description: this function is responsible of extracting the data.
 * 				:1000000000500020C9050108190601081906010859
 * 				|||||||||||                              CC->Checksum
 * 				|||||||||DD->Data
 * 				|||||||TT->Record Type
 * 				|||AAAA->Address
 * 				|LL->Record Length (0x10 == 16 bytes)
 * 				:->Colon
 ************************************************************************/
void parseData(uint8_t* record){
/* Local variables*/
	/* Array to hold the data after extracting it. */
	uint16_t data[100];
	/* Record length , low digit , high digit of the record length */
	uint8_t LL , LL_lowDigit , LL_highDigit;
	/* Array to hold the address and data digits. */
	uint8_t digits[4];
	/* Iterator to be used in the for loop. */
	uint8_t i;

/* converting record length from ASCII to hex. */
	/* converting the high digit of the record length from ASCII to hex */
	LL_highDigit = ASCII_TO_HEX(record[1]);
	/* converting the low digit of the record length from ASCII to hex */
	LL_lowDigit = ASCII_TO_HEX(record[2]);
	/* assigning the variable that should hold the record length with the *
	 * value after conversion.                                            */
	LL = (LL_highDigit << 4) | (LL_lowDigit);

/* converting address from ASCII to hex and forming the address. */
	/* converting each digit of the data from ASCII to hex */
	digits[0] = ASCII_TO_HEX(record[3]);
	digits[1] = ASCII_TO_HEX(record[4]);
	digits[2] = ASCII_TO_HEX(record[5]);
	digits[3] = ASCII_TO_HEX(record[6]);

/* forming the address */
	/* clearing the lower part of the address */
	address &= 0xFFFF0000;

	/* forming the address of the digits after  *
	 * converting them to hex format.           */
	address |= (digits[0]<<4*3)
			  |(digits[1]<<4*2)
			  |(digits[2]<<4*1)
			  |(digits[3]);

/* forming an array of the data to be flashed. */
	/* looping to half the record length as the record length is the  *
	 * number of bytes existing in the record data but we are forming *
	 * a 2-byte data length(1/2 word) so, we need to loop to half the *
	 * record length only.                                            */
	for(i = 0 ; i<(LL/2) ; i++){

		/* converting each digit from ASCII to hex */
		digits[0] = ASCII_TO_HEX(record[9  + (4*i)]);
		digits[1] = ASCII_TO_HEX(record[10 + (4*i)]);
		digits[2] = ASCII_TO_HEX(record[11 + (4*i)]);
		digits[3] = ASCII_TO_HEX(record[12 + (4*i)]);

		/* assigning the digits shifted to data that will be flashed *
		 * but take into consideration the little endian.            */
		data[(uint32_t)i] = (digits[2]<<4*3)
						   |(digits[3]<<4*2)
						   |(digits[0]<<4*1)
						   |(digits[1]);
	}

	/* flashing the data in the corresponding addresses. */
	FPEC_FlashWriteHexRecord(address, data, (LL/2));
}


/************************************************************************
 * Service name: Parser_parseRecord
 *
 * Parameters in: uint8_t * record
 *               (the record to be parsed to extract the upper part
 *                of the address or the data or the finish-record
 *                indication)
 *
 * Parameters in/out: None
 *
 * Parameters out: None
 *
 * Return: void
 *
 * Description: this function is responsible of processing the passed
 *              record to whether extracting the data, the upper part
 *              of the address or the lower part as well according to
 *              the record type that is included in each record, where
 *              if the record type is: 00 -> data.
 *                                     04 -> upper part of the address.
 *                                     01 -> end of the file.
 ************************************************************************/
void Parser_parseRecord(uint8_t* record){
/* Local variables:*/
	/* variable to hold the optionBytes value. */
	uint8_t optionByteVal = 0;
	/* getting the value of the option bytes. */
	FPEC_GetDataOptionByte(FPEC_DATA_OPTION_BYTE0, &optionByteVal);

	/* if the eighth digit of the record is: *
	 * 0 -> data                             *
	 * 4 -> upper part of the address        *
	 * 1 -> end of the file.                 */
	switch(record[8]){
	/* case -> data */
	case RECORD_TYPE_DATA:
		/* parse the data to flash it */
		parseData(record);
		break;

	/* case -> address upper part */
	case RECORD_TYPE_ADDRESS_UPPER_PART:
		/* parsing the upper part of the address */
		parseAddressUpperPart(record);

		/* if the address refers to the first application */
		if(address == APP_BANK_1_ADDRESS_UPPER_PART){
			/* Erasing the bank of the first application */
			FPEC_EraseBankArea(APP_1_PAGE_NUM,APP_1_SIZE);

			/* clearing the flag that indicates that the *
			 * first application is flashed correctly.   */
			CLEAR_BIT(optionByteVal , APP_1_BANK_FLAG);
		}
		/* if the address refers to the second application */
		else if(address == APP_BANK_2_ADDRESS_UPPER_PART){
			/* Erasing the bank of the second application */
			FPEC_EraseBankArea(APP_2_PAGE_NUM,APP_2_SIZE);

			/* clearing the flag that indicates that the  *
			 * second application is flashed correctly.   */
			CLEAR_BIT(optionByteVal , APP_2_BANK_FLAG);
		}
		else{
			/* error handling: this means that the passed address  *
			 * is not supported.                                   */
		}

		/* write the option bytes. */
		FPEC_WriteDataOptionByte(FPEC_DATA_OPTION_BYTE0, optionByteVal);
		break;
	/* case -> end of the file. */
	case RECORD_TYPE_END_OF_FILE:
		/* clearing the first two bits of the option byte DATA0 where *
		 * these bits indicate the current running program.           */
		CLEAR_BIT(optionByteVal , 0);
		CLEAR_BIT(optionByteVal , 1);

		/* if the upper part of the address reference to the first *
		 * bank.                                                   */
		if((address & 0xFFFF0000) == APP_BANK_1_ADDRESS_UPPER_PART){
			/* assigning the ID of APP1 in the option bytes */
			optionByteVal |= APP_1_ID;
			currentApp = APP_1_ID;

			/* setting the flag of the APP_1 bank in the option *
			 * bytes.                                           */
			SET_BIT(optionByteVal , APP_1_BANK_FLAG);
		}
		/* if the upper part of the address reference to the second *
		 * bank.                                                    */
		else if((address & 0xFFFF0000) == APP_BANK_2_ADDRESS_UPPER_PART){
			/* assigning the ID of APP2 in the option bytes */
			optionByteVal |= APP_2_ID;
			currentApp = APP_2_ID;

			/* setting the flag of the APP_2 bank in the option *
			 * bytes.                                           */
			SET_BIT(optionByteVal , APP_2_BANK_FLAG);
		}
		/* write the option bytes including the flag that indicates      *
		 * the first APP and the second APP are flashed correctly or not */
		FPEC_WriteDataOptionByte(FPEC_DATA_OPTION_BYTE0, optionByteVal);
	default:
		break;
	}
}

/************************************************************************
 * Service name: Parser_GetAppId
 *
 * Parameters in: None
 *
 * Parameters in/out: None
 *
 * Parameters out: APPs_ID * app_id
 *               (variable to hold the id of the current app)
 *
 * Return: void
 *
 * Description: this function reads the option bytes and assigns the
 *              app_id value with the id that is in the option byte,
 *              if the first 2 bits in option byte DATA0 == 1 then
 *              APP_1_ID and if 2 then APP_2_ID.
 ************************************************************************/
void Parser_GetAppId(APPs_ID * app_id){
	/* Local variable to hold the value of the option byte after  *
	 * reading it.                                                */
	uint8_t optionByteVal = 0;

	/* if the currentApp is NULL then this indicates that there is no *
	 * new application being flashed.                                 */
	if(currentApp == NULL){
		/* Get the app_id from the option byte. */
		FPEC_GetDataOptionByte(FPEC_DATA_OPTION_BYTE0, &optionByteVal);
		(*app_id) = optionByteVal &0x03;
	}
	/* if the currentApp variable holds any value other than NULL *
	 * then there is a new application that is flashed.           */
	else{
		(*app_id) = currentApp;
	}
}


/************************************************************************
 * Service name: Parser_SetAppId
 *
 * Parameters in: APPs_ID app_id
 * 				  (the id of the app to be set in the option byte)
 *
 * Parameters in/out: None
 *
 * Parameters out: None
 *
 * Return: void
 *
 * Description: this function sets the id bits in the option bytes
 *              with the passed value.
 ************************************************************************/
void Parser_SetAppId(APPs_ID app_id){
	/* Local variable to hold the option bytes value. */
	uint8_t optionByteVal = 0;

	/* reading the DATA0 option byte. */
	FPEC_GetDataOptionByte(FPEC_DATA_OPTION_BYTE0, &optionByteVal);

	/* clearing the id bits to assign the new id. */
	optionByteVal &= ~(0x03);

	/* Assigning the new id. */
	optionByteVal |= app_id;

	/* write the option byte value. */
	FPEC_WriteDataOptionByte(FPEC_DATA_OPTION_BYTE0, optionByteVal);
}

/************************************************************************
 * Service name: Parser_isAppAvailable
 *
 * Parameters in: APPs_ID app_id
 * 				  (the id of the app to be check if it exist or not)
 *
 * Parameters in/out: None
 *
 * Parameters out: None
 *
 * Return: void
 *
 * Description: this function checks whether the app that its id is
 *              passed exist or not.
 ************************************************************************/
uint8_t Parser_isAppAvailable(APPs_ID app_id){
	/* Local variable to hold the option byte value. */
	uint8_t optionByteVal = 0;
	/* Local variable to hold the status that indicates whether *
	 * this application exist or not.                           */
	uint8_t status = 0;

	/* getting the option byte value. */
	FPEC_GetDataOptionByte(FPEC_DATA_OPTION_BYTE0, &optionByteVal);

	/* if the passed id to be checked is APP_1 */
	if(app_id == APP_1_ID){
		/* checking the flag of APP_1 in the option bytes */
		status = optionByteVal >> APP_1_BANK_FLAG;
	}
	/* if the passed id to be checked is APP_2 */
	else if(app_id == APP_2_ID){
		/* checking the flag of the APP_2 in the option bytes */
		status = optionByteVal >> APP_2_BANK_FLAG;
	}
	return status;
}

/************************************************************************
 * Service name: Parser_ToggleAppId
 *
 * Parameters in: None
 *
 * Parameters in/out: None
 *
 * Parameters out: None
 *
 * Return: void
 *
 * Description: this function toggles the application id.
 ************************************************************************/
void Parser_ToggleAppId(void){
	/* Local variable to hold the current id. */
	uint8_t app_id = 0;
	/* getting the current app id. */
	Parser_GetAppId(&app_id);
	/* if the current app is APP_1 and APP_2 exists then toggle */
	if(app_id == APP_1_ID && Parser_isAppAvailable(APP_2_ID)){
		/* set the current app id with APP_2_ID */
		Parser_SetAppId(APP_2_ID);
	}
	/* if the current app is APP_2 and APP_1 exists then toggle */
	else if(app_id == APP_2_ID && Parser_isAppAvailable(APP_1_ID)){
		/* set the current app id with APP_1_ID */
		Parser_SetAppId(APP_1_ID);
	}
}
