/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 *          Mark Ehab Tawfik (201)
 *          Hazem Mohamed Ezzeldin (1297)
 *          Azza Saeed Mohammed Gad (912)
 *          MennaTullah Ahmed Farrag Hefny (116)
 * \date: 1/10/2023
 * \brief: private header file for LCD
 ******************************************************/

#ifndef COMMON_MACROS
#define COMMON_MACROS

/* commonly used macros */
#define READ_BIT(REG , BIT_NUM) ((REG>>BIT_NUM) & 0x01)
#define SET_BIT(REG , BIT_NUM) (REG |= (1<<BIT_NUM))
#define CLEAR_BIT(REG , BIT_NUM) (REG &= ~(1<<BIT_NUM))
#define TOGGLE_BIT(REG , BIT_NUM) (REG ^= (1<<BIT_NUM))
#define ROR(REG , BIT_NUM) (REG = (REG >> BIT_NUM) | (REG<<(sizeof(REG)*8 - BIT_NUM)))
#define ROL(REG , BIT_NUM) (REG = (REG << BIT_NUM) | (REG>>(sizeof(REG)*8 - BIT_NUM)))
#define BIT_IS_SET(REG , BIT_NUM) (REG & (1<<BIT_NUM))
#define BIT_IS_CLEAR(REG , BIT_NUM) (!(REG &(1<<BIT_NUM)))

/*-----------------------------------------------------------------------------------------------------------------*/
/*                                                                                   							   */
/*	Define a function-like macro called CONC to help us in concatenation of registers bits from config file 	   */
/*                                                                                  							   */
/*-----------------------------------------------------------------------------------------------------------------*/
#define CONC_8_BITS(b7,b6,b5,b4,b3,b2,b1,b0)        							    CONC_8_BITS_HELP(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_8_BITS_HELP(b7,b6,b5,b4,b3,b2,b1,b0)   							    0b##b7##b6##b5##b4##b3##b2##b1##b0
#define CONC_16_BITS(b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0)         CONC2_16_BITS_HELP(b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC2_16_BITS_HELP(b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0)   0b##b15##b14##b13##b12##b11##b10##b9##b8##b7##b6##b5##b4##b3##b2##b1##b0


#endif
