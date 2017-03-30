/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define Push_Button_Pin GPIO_PIN_13
#define Push_Button_GPIO_Port GPIOC
#define TEMP_2_Pin GPIO_PIN_0
#define TEMP_2_GPIO_Port GPIOC
#define TEMP_1_Pin GPIO_PIN_1
#define TEMP_1_GPIO_Port GPIOC
#define PRESSURE_1_Pin GPIO_PIN_2
#define PRESSURE_1_GPIO_Port GPIOC
#define PRESSURE_2_Pin GPIO_PIN_3
#define PRESSURE_2_GPIO_Port GPIOC
#define ACCEL_X_Pin GPIO_PIN_0
#define ACCEL_X_GPIO_Port GPIOA
#define ACCEL_Y_Pin GPIO_PIN_1
#define ACCEL_Y_GPIO_Port GPIOA
#define PRESSURE_3_Pin GPIO_PIN_3
#define PRESSURE_3_GPIO_Port GPIOA
#define ACCEL_Z_Pin GPIO_PIN_4
#define ACCEL_Z_GPIO_Port GPIOA
#define ON_BOARD_LED_Pin GPIO_PIN_5
#define ON_BOARD_LED_GPIO_Port GPIOA
#define TEMP_3_Pin GPIO_PIN_4
#define TEMP_3_GPIO_Port GPIOC
#define PRESSURE_1B0_Pin GPIO_PIN_0
#define PRESSURE_1B0_GPIO_Port GPIOB
#define Motor_Back_Pin GPIO_PIN_6
#define Motor_Back_GPIO_Port GPIOC
#define Motor_Front_Pin GPIO_PIN_8
#define Motor_Front_GPIO_Port GPIOC
#define Go_Pro_Trigger_Pin GPIO_PIN_9
#define Go_Pro_Trigger_GPIO_Port GPIOC
#define Motor_Interrupt_Pin GPIO_PIN_10
#define Motor_Interrupt_GPIO_Port GPIOC
#define Go_Pro_Interrupt_Pin GPIO_PIN_11
#define Go_Pro_Interrupt_GPIO_Port GPIOC
#define LED_1_Pin GPIO_PIN_8
#define LED_1_GPIO_Port GPIOB
#define LED_2_Pin GPIO_PIN_9
#define LED_2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
