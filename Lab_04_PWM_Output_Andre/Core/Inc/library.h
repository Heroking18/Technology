/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : library.h
  * @brief          : Header for library.c file.
  *
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
#ifndef __LIBRARY_H
#define __LIBRARY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

extern volatile uint32_t millis_counter;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/

/* USER CODE BEGIN EFP */

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

//*****************************************************************************
//              General-Purpose TIM4 Register CONFIG
void CMR_TIM4_config(TIM_TypeDef *, uint16_t, uint16_t, uint8_t, uint8_t, IRQn_Type);
void CCM_TIM4_config();

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
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

// TIMx_CR1 Center-aligned mode selection
#define EDGEALIGN			0x00
#define CENTERALIGN1		0x20
#define CENTERALIGN2		0x40
#define CENTERALIGN3		0x60

// TIMx_CR1 Direction
#define UPCOUNTER			~0x10
#define DOWNCOUNTER			0x10


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __LIBRARY_H */
