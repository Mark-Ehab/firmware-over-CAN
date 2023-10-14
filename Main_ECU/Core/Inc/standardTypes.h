/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 *          Mark Ehab Tawfik (201)
 *          Hazem Mohamed Ezzeldin (1297)
 *          Azza Saeed Mohammed Gad (912)
 *          MennaTullah Ahmed Farrag Hefny (116)
 * \date: 15/8/2023
 * \brief: header files for the standard types
 ******************************************************/

#ifndef STANDARDTYPES_H_
#define STANDARDTYPES_H_

#define uint8_t         unsigned char
#define sint8_t         char
#define uint16_t        unsigned short
#define sint16_t        short
#define uint32_t        unsigned int
#define sint32_t        int
#define uin64_t         unsigned long long
#define sint64_t        long long
#define float32_t       float
#define bool            char
#define STATUS          char
#define TRUE            (1U)
#define FALSE           (0U)
#define LOGIC_HIGH      (1U)
#define LOGIC_LOW       (0U)
#define E_OK            (1U)
#define E_NOK           (0U)
#define PIN_HIGH        (1U)
#define PIN_LOW         (0U)
#define STD_ON          (1U)
#define STD_OFF         (0U)
#define NULL            (0U)

typedef enum
{
	RT_OK  	        = 0,
	RT_NOK 	        = 1,
	NULL_POINTER	= 2,
	BUSY_FUNC		= 3
}ERROR_STATUS_t;

#endif /* STANDARDTYPES_H_ */
