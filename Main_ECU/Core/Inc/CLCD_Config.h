/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 *          Mark Ehab Tawfik (201)
 *          Hazem Mohamed Ezzeldin (1297)
 *          Azza Saeed Mohammed Gad (912)
 *          MennaTullah Ahmed Farrag Hefny (116)
 * \date: 1/10/2023
 * \brief: configuration header file for LCD
 ******************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*							  _____ _      _____ _____     _____             __ _                           */
/*							 / ____| |    / ____|  __ \   / ____|           / _(_)                          */
/*							| |    | |   | |    | |  | | | |     ___  _ __ | |_ _  __ _                     */
/*							| |    | |   | |    | |  | | | |    / _ \| '_ \|  _| |/ _` |                    */
/*							| |____| |___| |____| |__| | | |___| (_) | | | | | | | (_| |                    */
/*							 \_____|______\_____|_____/   \_____\___/|_| |_|_| |_|\__, |                    */
/*							                                                      __/  |                    */
/*			                                                                      |___/                     */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef HAL_CLCD_CONFIG_H_
#define HAL_CLCD_CONFIG_H_

/*-------------------------------------------------------*/
/* Select Character LCD Mode :-		       				 */
/* 		         	                        			 */
/* Options : - FOUR_BIT_MODE                       		 */
/*    	     - EIGHT_BIT_MODE 	              	    	 */
/*							 							 */
/*-------------------------------------------------------*/
#define CLCD_MODE 		        FOUR_BIT_MODE /* Default: EIGHT_BIT_MODE */

/*-------------------------------------------------------*/
/* Select Character LCD Data Port :-                     */
/* 		         	                                     */
/* Options : - PORT_A                                    */
/*    	     - PORT_B	                                 */
/*           - PORT_C	                                 */
/*	         - PORT_D	                                 */
/* 	                          		                     */
/*-------------------------------------------------------*/
#define CLCD_DATA_PORT 	   	     PORT_B /* Default: PORT_A */

/*-------------------------------------------------------*/
/* Select Character LCD Control Pins Port :-             */
/* 		         	                                     */
/* Options : - PORT_A                                    */
/*    	     - PORT_B	                                 */
/*           - PORT_C	                                 */
/*	         - PORT_D	                                 */
/* 	                          		 	                 */
/*-------------------------------------------------------*/
#define CLCD_CTRL_PINS_PORT 	  PORT_A /* Default: PORT_B */

/*-------------------------------------------------------*/
/* Select Character LCD RW Control Pin :-                */
/* 		         	                                     */
/* Options : - PIN_0                                     */
/*    	     - PIN_1	                                 */
/*           - PIN_2	                                 */
/*	         - PIN_3	                                 */
/*	         - PIN_4                                     */
/*	         - PIN_5                                     */
/*	         - PIN_6                                     */
/*           - PIN_7                                     */
/*			 - PIN_8                                     */
/*           - PIN_9                                     */
/*           - PIN_10                                    */
/*           - PIN_11                                    */
/*           - PIN_12                                    */
/*           - PIN_13                                    */
/*           - PIN_14                                    */
/*			 - PIN_15                                    */
/* 	                          		 	                 */
/*-------------------------------------------------------*/
#define CLCD_RW_PIN    		       PIN_0 /* Default : PIN_0 */

/*-------------------------------------------------------*/
/* Select Character LCD RS Control Pin :-                */
/* 		         	                                     */
/* Options : - PIN_0                                     */
/*    	     - PIN_1	                                 */
/*           - PIN_2	                                 */
/*	         - PIN_3	                                 */
/*	         - PIN_4                                     */
/*	         - PIN_5                                     */
/*	         - PIN_6                                     */
/*           - PIN_7                                     */
/*			 - PIN_8                                     */
/*           - PIN_9                                     */
/*           - PIN_10                                    */
/*           - PIN_11                                    */
/*           - PIN_12                                    */
/*           - PIN_13                                    */
/*           - PIN_14                                    */
/*			 - PIN_15                                    */
/* 	                          		 	                 */
/*-------------------------------------------------------*/
#define CLCD_RS_PIN    		       PIN_9 /* Default : PIN_1 */

/*-------------------------------------------------------*/
/* Select Character LCD E Control Pin :-                 */
/* 		         	                                     */
/* Options : - PIN_0                                     */
/*    	     - PIN_1	                                 */
/*           - PIN_2	                                 */
/*	         - PIN_3	                                 */
/*	         - PIN_4                                     */
/*	         - PIN_5                                     */
/*	         - PIN_6                                     */
/*           - PIN_7                                     */
/*			 - PIN_8                                     */
/*           - PIN_9                                     */
/*           - PIN_10                                    */
/*           - PIN_11                                    */
/*           - PIN_12                                    */
/*           - PIN_13                                    */
/*           - PIN_14                                    */
/*			 - PIN_15                                    */
/* 	                          		 	                 */
/*-------------------------------------------------------*/
#define CLCD_E_PIN   	            PIN_8 /* Default : PIN_2 */

/*-------------------------------------------------------*/
/* Select Character LCD E Data Pins :-                   */
/* 		         	                                     */
/* Options : - PIN_0                                     */
/*    	     - PIN_1	                                 */
/*           - PIN_2	                                 */
/*	         - PIN_3	                                 */
/*	         - PIN_4                                     */
/*	         - PIN_5                                     */
/*	         - PIN_6                                     */
/*           - PIN_7                                     */
/*			 - PIN_8                                     */
/*           - PIN_9                                     */
/*           - PIN_10                                    */
/*           - PIN_11                                    */
/*           - PIN_12                                    */
/*           - PIN_13                                    */
/*           - PIN_14                                    */
/*			 - PIN_15                                    */
/* 	                          		 	                 */
/*-------------------------------------------------------*/
#define CLCD_D0_PIN                 PIN_0
#define CLCD_D1_PIN                 PIN_1
#define CLCD_D2_PIN                 PIN_2
#define CLCD_D3_PIN                 PIN_3
#define CLCD_D4_PIN                 PIN_15
#define CLCD_D5_PIN                 PIN_14
#define CLCD_D6_PIN                 PIN_13
#define CLCD_D7_PIN                 PIN_12

#endif /* HAL_CLCD_CONFIG_H_ */
