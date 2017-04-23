/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "fatfs.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "User_Functions.h"
#include "sd_diskio.h"
#include "stm32_adafruit_sd.h"
#include "stm32l0xx_nucleo.h"

#define ADC_ON 0
extern Diskio_drvTypeDef SD_Driver;

void SystemClock_Config(void);
void Error_Handler(void);
static void MX_NVIC_Init(void);

/* private variables */

/* sd card globals: */
FATFS SDFatFs;
FIL MyFile;
char SDPath[4];

/* end sd card globals */

int main(void)
{
		/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_FATFS_Init();
  MX_ADC_Init();
  MX_USART2_UART_Init();
	
	
  /* Initialize interrupts */
  MX_NVIC_Init();

  // SD card initialization
	
	FRESULT res;
	SD_CardInfo sd_info;
	uint32_t byteswritten, bytesread; // test size of write/read to confirm success
	uint8_t wtext[] = "This is a test of the SD card for RockSat REX-B";
	uint16_t rtext[100]; // read from sd card test array
	
	BSP_SD_Init();
	BSP_SD_GetCardInfo(&sd_info);
	
	FATFS_LinkDriver(&SD_Driver, SDPath); // link generic fatfs with sd card driver
	f_mount(&SDFatFs, (TCHAR const*)SDPath, 0); /// mount logical drive (0 is delayed mount)
	f_mkfs((TCHAR const*)SDPath, 0, 0); // create file system on logical drive.
	f_open(&MyFile, "STM32.TXT", FA_CREATE_ALWAYS | FA_WRITE); // open/create file
	f_write(&MyFile, wtext, sizeof(wtext), (UINT*)&byteswritten); // write data to file.
	f_read(&MyFile, rtext, sizeof(rtext), (UINT*)&bytesread); // read data back from file.
	f_close(&MyFile); // close file
	if(byteswritten == bytesread) { // flip LED to indicate success
		HAL_GPIO_WritePin(ON_BOARD_LED_GPIO_Port, ON_BOARD_LED_Pin, GPIO_PIN_SET);
	}
	
	
	/*************** 
	TODO: 
		- set CS gpio pin in cube and in stm32l0xx_nucleo.h
		- remove LCD and other useless code in stm32l0xx_nucleo.h/.c, stm32_adafruit_sd.h/.c
		- determine if we should use stm32_adafruit_sd or just use fatfs?
		- housekeeping to clean up and comment necessary code
	***************/
		/* main functionality to implement :   
			* confirm .csv file formatting
			* write labels for each column (sensor names in order)
			* buffer for ADC conversion data to be written
			* once buffer reaches sd block size limit, write data to sd card.
					(sd cards are written one block at a time.)
			* once buffer has been emptied write a new line.
			* repeat
			
	*/
	
	/* this code uses fatfs and sd_diskio and is probably right, using it as a general
			structure for our code */
	
//	if (FATFS_LinkDriver(&SD_Driver, SDPath) == 0) {
//		if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) != FR_OK) {
//			/* fatfs init error */
//			Error_Handler();
//		}
//		else {
//			if (f_mkfs((TCHAR const*)SDPath, 0, 0) != FR_OK) {
//				/* fatfs format error */
//				Error_Handler();
//			}
//			else {
//				if(f_open(&MyFile, "STM32.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) {
//					/* 'STM32.TXT' file open for write error.*/
//					Error_Handler();
//				}
//				else {
//					/* write data to the file */
//				res = f_write(&MyFile, wtext, sizeof(wtext), (void*)&byteswritten);
//					
//					/* close the file */
//					if(f_close(&MyFile) != FR_OK) {
//						Error_Handler();
//					}
//					
//					if((byteswritten == 0) || (res!= FR_OK)) {
//						/* stm32 file write or eof error */
//						Error_Handler();
//					}
//					else {
//						if(f_open(&MyFile, "STM32.TXT", FA_READ) != FR_OK) {
//							/* file open for read error */
//							Error_Handler();
//						}
//						else {
//							// read data from file
//							res = f_read(&MyFile, rtext, sizeof(rtext), (UINT*)&bytesread);
//							
//							if((bytesread == 0) || (res != FR_OK)) {
//								/* file read or eof error */
//								Error_Handler();
//							}
//							else {
//								// close the file
//								f_close(&MyFile);
//								
//								if((bytesread != byteswritten)) {
//									// read data different from expected data
//									Error_Handler();
//								}
//								else {
//									// flip led for success.
//									HAL_GPIO_WritePin(ON_BOARD_LED_GPIO_Port, ON_BOARD_LED_Pin, GPIO_PIN_SET);
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
/* end stolen SD code */
  /* USER CODE BEGIN 2 */
	\

  while (1)
  {

  }


}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** NVIC Configuration
*/
static void MX_NVIC_Init(void)
{
  /* DMA1_Channel2_3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
		UNUSED(3);
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
