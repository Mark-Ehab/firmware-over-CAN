/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 *          Mark Ehab Tawfik (201)
 *          Hazem Mohamed Ezzeldin (1297)
 *          Azza Saeed Mohammed Gad (912)
 *          MennaTullah Ahmed Farrag Hefny (116)
 * \date: 1/10/2023
 * \brief: private header file for LCD
 ******************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*																									        */
/*						  _____ _      _____ _____    _____      _            _                             */
/*						 / ____| |    / ____|  __ \  |  __ \    (_)          | |                            */
/*						| |    | |   | |    | |  | | | |__) | __ ___   ____ _| |_ ___                       */
/*						| |    | |   | |    | |  | | |  ___/ '__| \ \ / / _` | __/ _ \                      */
/*						| |____| |___| |____| |__| | | |   | |  | |\ V / (_| | ||  __/                      */
/*						 \_____|______\_____|_____/  |_|   |_|  |_| \_/ \__,_|\__\___|                      */
/*																									        */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef HAL_CLCD_PRIVATE_H_
#define HAL_CLCD_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             CONFIGURATION OPTIONS VALUES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* CLCD Operation Modes */
#define FOUR_BIT_MODE		    1U
#define EIGHT_BIT_MODE 		    2U

/* CLCD CTRL & Data Port Values */
#define PORT_A                  0U
#define PORT_B                  1U
#define PORT_C                  2U
#define PORT_D                  3U

/* CLCD CTRL & Data Pin Values */
#define PIN_0                   0U
#define PIN_1                   1U
#define PIN_2                   2U
#define PIN_3                   3U
#define PIN_4                   4U
#define PIN_5                   5U
#define PIN_6                   6U
#define PIN_7                   7U
#define PIN_8                   8U
#define PIN_9                   9U
#define PIN_10                  10U
#define PIN_11                  11U
#define PIN_12                  12U
#define PIN_13                  13U
#define PIN_14                  14U
#define PIN_15                  15U

#endif /* HAL_CLCD_PRIVATE_H_ */
