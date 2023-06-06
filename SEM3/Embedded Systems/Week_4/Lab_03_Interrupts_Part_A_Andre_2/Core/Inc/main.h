/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
extern volatile int8_t flag;
extern volatile int8_t flag2;
extern volatile uint32_t millis_counter;
extern volatile int32_t timerCounter;
extern volatile int32_t timerCounter2;
extern volatile uint32_t previous_button0_time;
extern volatile uint32_t previous_button1_time;
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

//*****************************************************************************
//                         TRIGGER SELCETION CONFIG
typedef enum
{
	RISING_EDGE,
	FALLING_EDGE,
	RISING_FALLING_EDGE
}edge_select;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

void Button0_Press();
void Button1_Press();

//*****************************************************************************
//                             SysTick CONFIG
void SysTick_Init(uint32_t);
uint32_t millis();

//*****************************************************************************
//                             GPIO PIN CONFIG
void SetMode(GPIO_TypeDef *, uint8_t, uint8_t);
void SetType(GPIO_TypeDef *, uint8_t, uint8_t);
void SetSpeed(GPIO_TypeDef *, uint8_t, uint8_t);
void SetPullType(GPIO_TypeDef *, uint8_t, uint8_t);
void SetPin(GPIO_TypeDef *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

//*****************************************************************************
//                             INTERRUPT CONFIG
void config_gpio_interrupt(GPIO_TypeDef *, uint32_t, edge_select);
void enable_gpio_interrupt(uint32_t, IRQn_Type, uint8_t);
void reset_interrupt(uint32_t);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

// Systick register
#define SysTick_CTRL_CLKSOURCE 0x4UL
#define SysTick_CTRL_TICKINT   0x2UL
#define SysTick_CTRL_ENABLE    0x1UL

// GPIO port mode register
#define INPUT    			0x00
#define OUTPUT   			0x01
#define ALTFUNCTMODE 		0x02
#define ANALOG   			0x03

// GPIO port output type register
#define PUSHPULL 			0x00
#define OUTPUTDRAIN 		0x01

// GPIO port output speed register
#define LOWSPEED 			0x00
#define MEDSPEED 			0x01
#define HISPEED  			0x03

// GPIO port pull-up/pull-down register
#define NOPULL   			0x00
#define PULLUP   			0x01
#define PULLDOWN 			0x02

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
