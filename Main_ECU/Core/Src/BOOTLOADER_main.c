/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../Inc/standardTypes.h"

#include "../Inc/SCB_Interface.h"
#include "../Inc/BOOTLOADER_main.h"
#include "../Inc/parse.h"
#include "../Inc/CLCD_Interface.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* declaring a pointer to function */
typedef void(* fun_ptr)(void);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/***************************************************************************
 *                           Global variables                              *
 ***************************************************************************/

/* this variable is externed in stm32f1xx_it.c to be used in SysTick_Handler *
 * USER_definedTicks = number of seconds                               */
uint32_t USER_definedTicks = APP_TIME_OUT_VAL;
/*-----------------------------------------------*/

/* CAN variables: */
/* CAN header type */
CAN_HandleTypeDef hcan;
/* buffer to receive the data */
uint8_t CAN_RxBuffer[APP_BUFFER_MAX_ELEMENTS] = {0};
/* iterator to access each element in the CAN_RxBuffer */
uint8_t CAN_i = 0;
/* Tx and Rx headers */
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
/*-----------------------------------------------------*/

/* Flags: */
/* timeout flag */
uint8_t Flag_timeOut = 0;
/* data received flag */
uint8_t Flag_CAN = 0;
/* switch the application flag */
uint8_t FLAG_AppSwitch = 0;
/*--------------------------------*/

/* pointer to function that will be called */
fun_ptr addr_to_call = 0;
/*-----------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);

/* USER CODE BEGIN PFP */

/* initialize the SysTick */
void USER_SysTickInit(void);
/* deinitialize the SysTick */
void USER_SysTickDeinit(void);
/* SysTick call back function */
void USER_SysTickCallBack(void);
/* clear the CAN RX buffer */
void USER_clearRxBuffer(void);
/* function to jump to APP1 */
void BOOTLOADER_gumpToAPP1(void);
/* function to jump to APP2 */
void BOOTLOADER_gumpToAPP2(void);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
/* Local variables: */
	/* variable to hold the requires application ID */
	APPs_ID app_id;

	/* Flag to write on the LCD once */
	uint8_t Flag_once = 1;

	/* String to be displayed on the LCD */
	uint8_t * LCD_String = "BOOTLOADER";

	/* data to be sent */
	uint8_t TxData = 3;

	/* CAN TX mailbox*/
	uint32_t TxMailbox;

	/* CAN buffer to receive dummy data */
	uint8_t CAN_RxDummyBuffer;

	/* CAN RX header parameters */
	RxHeader.DLC = 1;
	RxHeader.IDE = CAN_ID_STD;
	RxHeader.RTR = CAN_RTR_DATA;
	RxHeader.StdId = 0x103;

	/* CAN TX header parameters */
	TxHeader.DLC = 1;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = 0x030;

/* MCU Configuration--------------------------------------------------------*/
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
/* CAN: */
	/* initializing the CAN driver. */
	MX_CAN_Init();
	/* Start the CAN driver */
	HAL_CAN_Start(&hcan);
	/* Enable the CAN interrupt mode */
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

	/* receive in the CAN RX buffer */
	HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &RxHeader, &CAN_RxDummyBuffer);
	HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox);


/* SysTick: */
	/* updates the value of the SystemCoreClock variable */
	SystemCoreClockUpdate();
	/* configuring the clock to trigger interrupt each 1 second */
	SysTick_Config(SystemCoreClock);

/* Super loop */
	while (1)
	{
/* LCD: */
		/* initialize the LCD */
		CLCD_Init();
		/* clear the LCD */
		CLCD_ClearDisplay();
		/* write the string on the LCD */
		CLCD_WriteString(LCD_String);

		/* assigning the timeout flag */
		Flag_timeOut = 0;
		/* initializing the SysTick */
		USER_SysTickInit();

		/* while the timer isn't out yet */
		while(APP_TIMEOUT_FLAG_NOT_SET == Flag_timeOut)
		{
			/* if the CAN flag is raised */
			if(Flag_CAN)
			{
				/* LCD displaying: Flashing... */
				if(Flag_once){
					/* reseting the Flag */
					Flag_once = 0;
					/* moving the cursor to write in the second row */
					CLCD_MoveCursor(CLCD_ROW_1, CLCD_COLUMN_0);
					/* writing "flashing..." on the LCD */
					CLCD_WriteString("flashing...");
				}
				/* reseting the CAN flag */
				Flag_CAN = 0;
				/* disabling the SysTick timer */
				USER_SysTickDeinit();

				/* check if the whole record is received or not */
				if(APP_END_OF_RECORD == CAN_RxBuffer[CAN_i-1])
				{
					/* reseting the CAN iterator */
					CAN_i = 0;
					/* parsing the record */
					Parser_parseRecord(CAN_RxBuffer);
					/* clearing the CAN RX buffer to receive a new record */
					USER_clearRxBuffer();
				}

				/* if the record isn't received completely yet */
				else
				{
					/* do nothing */
				}
				/* sending an ACK to the Gateway ECU */
				HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox);
				/* reinitializing the SysTick timer */
				USER_SysTickInit();
			}
			/* if the CAN flag is not raised yet */
			else
			{
				/* do nothing */
			}
		}

		/* Getting the requires APP ID */
		Parser_GetAppId(&app_id);

		/* if the button is pressed */
		if(FLAG_AppSwitch)
		{
			/* checking on the current APP and the availability of the other APP */

			/* if the current APP is APP_1 and APP_2 is available then jump to APP_2 */
			if(APP_1_ID == app_id && Parser_isAppAvailable(APP_2_ID))
			{
				/* displaying on LCD: switching... */
				/* Clearing the LCD */
				CLCD_ClearDisplay();
				/* display */
				CLCD_WriteString("switch to APP2");

				HAL_Delay(2);

				/* toggle the APP ID to indicate that the current APP is APP_2 not APP_1*/
				Parser_ToggleAppId();
				/* Jump to APP2 */
				BOOTLOADER_gumpToAPP2();
			}
			/* if the current APP is APP_1 and APP_2 is not available then jump to APP_1 */
			else if(APP_1_ID == app_id)
			{
				/* displaying on LCD: no APP available... */
				/* Clearing the LCD */
				CLCD_ClearDisplay();
				/* divide the string to fit the LCD size */
				CLCD_MoveCursor(CLCD_ROW_0, CLCD_COLUMN_3);
				/* write on the first row */
				CLCD_WriteString("no APP");
				/* move the cursor to the second row */
				CLCD_MoveCursor(CLCD_ROW_1, CLCD_COLUMN_1);
				/* write on the second row */
				CLCD_WriteString("available...");

				HAL_Delay(2);

				/* Jump to APP1 */
				BOOTLOADER_gumpToAPP1();
			}
			/* if the current APP is APP_2 and APP_1 is available then jump to APP_1 */
			else if(APP_2_ID == app_id && Parser_isAppAvailable(APP_1_ID))
			{
				/* displaying on LCD: switching... */
				/* Clearing the LCD */
				CLCD_ClearDisplay();
				/* display */
				CLCD_WriteString("switch to APP1");

				HAL_Delay(2);

				/* toggle the APP ID to indicate that the current APP is APP_1 not APP_2 */
				Parser_ToggleAppId();
				/* Jump to APP1 */
				BOOTLOADER_gumpToAPP1();
			}
			/* if the current APP is APP_2 and APP_1 is not available then jump to APP_2 */
			else if(APP_2_ID == app_id)
			{
				/* displaying on LCD: no APP available... */
				/* Clearing the LCD */
				CLCD_ClearDisplay();
				/* divide the string to fit the LCD size */
				CLCD_MoveCursor(CLCD_ROW_0, CLCD_COLUMN_3);
				/* write on the first row */
				CLCD_WriteString("no APP");
				/* move the cursor to the second row */
				CLCD_MoveCursor(CLCD_ROW_1, CLCD_COLUMN_1);
				/* write on the second row */
				CLCD_WriteString("available...");

				HAL_Delay(2);

				/* Jump to APP2 */
				BOOTLOADER_gumpToAPP2();
			}
		}
		/* if the button isn't pressed */
		else{

			/* if the current APP is APP1 */
			if(APP_1_ID == app_id)
			{
				/* displaying on LCD: jumping... */
				/* Clearing the LCD */
				CLCD_ClearDisplay();
				/* display */
				CLCD_WriteString("jumping to APP1");

				HAL_Delay(2);

				/* jump to APP_1 */
				BOOTLOADER_gumpToAPP1();
			}
			/* if the current APP is APP2 */
			else if(APP_2_ID == app_id)
			{
				/* displaying on LCD: jumping... */
				/* Clearing the LCD */
				CLCD_ClearDisplay();
				/* display */
				CLCD_WriteString("jumping to APP2");

				HAL_Delay(2);

				/* jump to APP_2 */
				BOOTLOADER_gumpToAPP2();
			}
		}
	}
}


/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief CAN Initialization Function
 * @param None
 * @retval None
 */
static void MX_CAN_Init(void)
{

	/* USER CODE BEGIN CAN_Init 0 */

	/* USER CODE END CAN_Init 0 */

	/* USER CODE BEGIN CAN_Init 1 */

	/* USER CODE END CAN_Init 1 */
	hcan.Instance = CAN1;
	hcan.Init.Prescaler = 16;
	hcan.Init.Mode = CAN_MODE_NORMAL;
	hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan.Init.TimeSeg1 = CAN_BS1_2TQ;
	hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
	hcan.Init.TimeTriggeredMode = DISABLE;
	hcan.Init.AutoBusOff = DISABLE;
	hcan.Init.AutoWakeUp = DISABLE;
	hcan.Init.AutoRetransmission = DISABLE;
	hcan.Init.ReceiveFifoLocked = DISABLE;
	hcan.Init.TransmitFifoPriority = DISABLE;
	if (HAL_CAN_Init(&hcan) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN CAN_Init 2 */
	CAN_FilterTypeDef canfilterconfig;


	canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
	canfilterconfig.FilterBank = 10;  // anything between 0 to SlaveStartFilterBank
	canfilterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	canfilterconfig.FilterIdHigh = 0x0000;
	canfilterconfig.FilterIdLow = 0x0000;
	canfilterconfig.FilterMaskIdHigh = 0x0000;
	canfilterconfig.FilterMaskIdLow = 0x0000;
	canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
	canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
	canfilterconfig.SlaveStartFilterBank = 0;  // 13 to 27 are assigned to slave CAN (CAN 2) OR 0 to 12 are assigned to CAN1

	HAL_CAN_ConfigFilter(&hcan, &canfilterconfig);

	/* USER CODE END CAN_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA2 PA8 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/*************************************************************
 * Service name: BOOTLOADER_gumpToAPP1
 *
 * parameter in: None
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: function to jump to application number 1
 *************************************************************/
void BOOTLOADER_gumpToAPP1(void){
	/* shift the vector table to that of APP_1 */
	SCB_ShiftInterruptVectorTable(APP_1_VECTOR_TABLE_ADDRESS);
	/* assign the address to call variable to the address of APP_1 */
	addr_to_call = *(fun_ptr*)(APP_1_RESET_HANDLER_ADDRESS);
	/* deinitializing the HAL */
	HAL_DeInit();
	/* jump to APP_1 by calling this pointer */
	addr_to_call();
}

/***************************************************************
 * Service name: BOOTLOADER_gumpToAPP2
 *
 * parameter in: None
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: function to jump to application number 2
 ***************************************************************/
void BOOTLOADER_gumpToAPP2(void){
	/* shift the vector table to that of APP_2 */
	SCB_ShiftInterruptVectorTable(APP_2_VECTOR_TABLE_ADDRESS);
	/* assign the address to call variable to the address of APP_2 */
	addr_to_call = *(fun_ptr*)(APP_2_RESET_HANDLER_ADDRESS);
	/* deinitializing the HAL */
	HAL_DeInit();
	/* jump to APP_2 by calling this pointer */
	addr_to_call();
}

/***************************************************************
 * Service name: USER_SysTickInit
 *
 * parameter in: None
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: initializing the SysTick timer
 ***************************************************************/
void USER_SysTickInit(void){
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	SysTick->CTRL = (SysTick_CTRL_TICKINT_Msk|
			SysTick_CTRL_ENABLE_Msk|
			SysTick_CTRL_CLKSOURCE_Msk);
}

/***************************************************************
 * Service name: USER_SysTickDeinit
 *
 * parameter in: None
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: deinitializing the SysTick timer
 ***************************************************************/
void USER_SysTickDeinit(void){
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
}

/***************************************************************
 * Service name: USER_SysTickCallBack
 *
 * parameter in: None
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: function to be called when the time is out
 ***************************************************************/
void USER_SysTickCallBack(void){
	/* toggle a LED to indicate that the time is up */
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
	/* setting the time out flag */
	Flag_timeOut = 1;
}

/***************************************************************
 * Service name: USER_clearRxBuffer
 *
 * parameter in: None
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: function to clear the CAN RX buffer
 ***************************************************************/
void USER_clearRxBuffer(void){
	/* looping over the CAN RX buffer */
	for(uint8_t clear_i = 0; clear_i<APP_BUFFER_MAX_ELEMENTS ; clear_i++){
		/* clearing the buffer */
		CAN_RxBuffer[(uint32_t)clear_i] = 0;
	}
}

/***************************************************************
 * Service name: HAL_CAN_RxFifo0MsgPendingCallback
 *
 * parameter in: None
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: CAN callback function
 ***************************************************************/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	/* raise the CAN flag */
	Flag_CAN = 1;
	/* toggle a led that indicates a reception*/
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
	/* receive in the CAN RX buffer */
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, &CAN_RxBuffer[CAN_i]);
	/* incrementing the iterator of the CAN */
	CAN_i++;
}

/***************************************************************
 * Service name: HAL_GPIO_EXTI_Callback
 *
 * parameter in: None
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: External callback function
 ***************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pins){
	/* raise the switch flag */
	FLAG_AppSwitch = 1;
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
