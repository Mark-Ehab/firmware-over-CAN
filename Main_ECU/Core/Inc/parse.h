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

#ifndef INC_PARSE_H_
#define INC_PARSE_H_

/* record types: */
#define RECORD_TYPE_DATA                 '0'
#define RECORD_TYPE_ADDRESS_UPPER_PART   '4'
#define RECORD_TYPE_END_OF_FILE          '1'

/*----------------------------------------------------------------------*
 *                      Functions prototypes                            *
 *----------------------------------------------------------------------*/


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
uint8_t ASCII_TO_HEX(uint8_t ASCII_data);

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
void parseAddressUpperPart(uint8_t * record);

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
void parseData(uint8_t* record);

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
void Parser_parseRecord(uint8_t* dataBuffer);

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
void Parser_GetAppId(APPs_ID * app_id);

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
void Parser_SetAppId(APPs_ID app_id);

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
uint8_t Parser_isAppAvailable(APPs_ID app_id);

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
void Parser_ToggleAppId(void);


#endif /* INC_PARSE_H_ */
