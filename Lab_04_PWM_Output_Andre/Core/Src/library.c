/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : library.c
  * @brief          : Private library
  *
  * @attention
  *
  * Copyright (c) 2022
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "library.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

//*****************************************************************************
//                             SysTick Config
void SysTick_Init(uint32_t ticks){
	SysTick->CTRL = 0;			// Disable SysTick
	SysTick->LOAD = ticks - 1;  // Set reload register

	// Set interrupt priority of SysTick to least urgency (i.e., largest priority value)
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);

    SysTick->VAL = 0;             // Reset the SysTick counter value. Software should always clear during the initialization.

    // Select processor clock: 1 = processor clock; 0 = external clock
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;

    // Enables SysTick interrupt, 1 = Enable, 0 = Disable
    SysTick->CTRL |= SysTick_CTRL_TICKINT;

    // Enable SysTick
    SysTick->CTRL |= SysTick_CTRL_ENABLE;
}

uint32_t millis()
{
	return millis_counter;
}

//*****************************************************************************
//                         Register settings for GPIO
void SetMode(GPIO_TypeDef * PORT, uint8_t pin, uint8_t mode){
	PORT->MODER |= (mode << (pin * 2)); // Times 2 because register occupies 2 bits for each MODER.
}

void SetType(GPIO_TypeDef * PORT, uint8_t pin, uint8_t type){
	PORT->OTYPER |= (type << pin);
}

void SetSpeed(GPIO_TypeDef * PORT, uint8_t pin, uint8_t speed){
	PORT->OSPEEDR |= (speed << (pin * 2));
}

void SetPullType(GPIO_TypeDef * PORT, uint8_t pin, uint8_t pulltype){
	PORT->PUPDR |= (pulltype << (pin * 2));
}

void SetPin(GPIO_TypeDef * PORT, uint8_t pin, uint8_t mode, uint8_t type, uint8_t speed, uint8_t pulltype){
	SetMode(PORT, pin, mode);
	SetType(PORT, pin, type);
	SetSpeed(PORT, pin, speed);
	SetPullType(PORT, pin, pulltype);
}

//*****************************************************************************
//                           Interrupt CONFIG
void config_gpio_interrupt(GPIO_TypeDef *PORT, uint32_t pin, edge_select edge)
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;	//	9.4.7 APB2 peripheral clock enable register (RCC_APB2ENR)

	/*****************  PORTA configuration for SYSCFG_EXTICRx  **************/
	if(PORT == GPIOA)
	{
		switch(pin)
		{
		/*****************  Bit configuration for SYSCFG_EXTICR1 register  **************/
		case 0:
		SYSCFG->EXTICR[0] |= (SYSCFG_EXTICR1_EXTI0 & SYSCFG_EXTICR1_EXTI0_PA);	/*!< PA[0] pin */
		break;
		case 1:
		SYSCFG->EXTICR[1] |= (SYSCFG_EXTICR1_EXTI1 & SYSCFG_EXTICR1_EXTI1_PA);	/*!< PA[1] pin */
		break;
		case 2:
		SYSCFG->EXTICR[2] |= (SYSCFG_EXTICR1_EXTI2 & SYSCFG_EXTICR1_EXTI2_PA);	/*!< PA[2] pin */
		break;
		case 3:
		SYSCFG->EXTICR[3] |= (SYSCFG_EXTICR1_EXTI3 & SYSCFG_EXTICR1_EXTI3_PA);	/*!< PA[3] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR2 register  **************/
		case 4:
		SYSCFG->EXTICR[4] |= (SYSCFG_EXTICR2_EXTI4 & SYSCFG_EXTICR2_EXTI4_PA);	/*!< PA[4] pin */
		break;
		case 5:
		SYSCFG->EXTICR[5] |= (SYSCFG_EXTICR2_EXTI5 & SYSCFG_EXTICR2_EXTI5_PA);	/*!< PA[5] pin */
		break;
		case 6:
		SYSCFG->EXTICR[6] |= (SYSCFG_EXTICR2_EXTI6 & SYSCFG_EXTICR2_EXTI6_PA);	/*!< PA[6] pin */
		break;
		case 7:
		SYSCFG->EXTICR[7] |= (SYSCFG_EXTICR2_EXTI7 & SYSCFG_EXTICR2_EXTI7_PA);	/*!< PA[7] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR3 register  **************/
		case 8:
		SYSCFG->EXTICR[8] |= (SYSCFG_EXTICR3_EXTI8 & SYSCFG_EXTICR3_EXTI8_PA);	/*!< PA[8] pin */
		break;
		case 9:
		SYSCFG->EXTICR[9] |= (SYSCFG_EXTICR3_EXTI9 & SYSCFG_EXTICR3_EXTI9_PA);	/*!< PA[9] pin */
		break;
		case 10:
		SYSCFG->EXTICR[10] |= (SYSCFG_EXTICR3_EXTI10 & SYSCFG_EXTICR3_EXTI10_PA);	/*!< PA[10] pin */
		break;
		case 11:
		SYSCFG->EXTICR[11] |= (SYSCFG_EXTICR3_EXTI11 & SYSCFG_EXTICR3_EXTI11_PA);	/*!< PA[11] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR4 register  **************/
		case 12:
		SYSCFG->EXTICR[12] |= (SYSCFG_EXTICR4_EXTI12 & SYSCFG_EXTICR4_EXTI12_PA);	/*!< PA[12] pin */
		break;
		case 13:
		SYSCFG->EXTICR[13] |= (SYSCFG_EXTICR4_EXTI13 & SYSCFG_EXTICR4_EXTI13_PA);	/*!< PA[13] pin */
		break;
		case 14:
		SYSCFG->EXTICR[14] |= (SYSCFG_EXTICR4_EXTI14 & SYSCFG_EXTICR4_EXTI14_PA);	/*!< PA[14] pin */
		break;
		case 15:
		SYSCFG->EXTICR[15] |= (SYSCFG_EXTICR4_EXTI15 & SYSCFG_EXTICR4_EXTI15_PA);	/*!< PA[15] pin */
		break;
		}
	}

	/*****************  PORTB configuration for SYSCFG_EXTICRx  **************/
	if(PORT == GPIOB)
	{
		switch(pin)
		{
		/*****************  Bit configuration for SYSCFG_EXTICR1 register  **************/
		case 0:
		SYSCFG->EXTICR[0] |= (SYSCFG_EXTICR1_EXTI0 & SYSCFG_EXTICR1_EXTI0_PB);	/*!< PB[0] pin */
		break;
		case 1:
		SYSCFG->EXTICR[1] |= (SYSCFG_EXTICR1_EXTI1 & SYSCFG_EXTICR1_EXTI1_PB);	/*!< PB[1] pin */
		break;
		case 2:
		SYSCFG->EXTICR[2] |= (SYSCFG_EXTICR1_EXTI2 & SYSCFG_EXTICR1_EXTI2_PB);	/*!< PB[2] pin */
		break;
		case 3:
		SYSCFG->EXTICR[3] |= (SYSCFG_EXTICR1_EXTI3 & SYSCFG_EXTICR1_EXTI3_PB);	/*!< PB[3] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR2 register  **************/
		case 4:
		SYSCFG->EXTICR[4] |= (SYSCFG_EXTICR2_EXTI4 & SYSCFG_EXTICR2_EXTI4_PB);	/*!< PB[4] pin */
		break;
		case 5:
		SYSCFG->EXTICR[5] |= (SYSCFG_EXTICR2_EXTI5 & SYSCFG_EXTICR2_EXTI5_PB);	/*!< PB[5] pin */
		break;
		case 6:
		SYSCFG->EXTICR[6] |= (SYSCFG_EXTICR2_EXTI6 & SYSCFG_EXTICR2_EXTI6_PB);	/*!< PB[6] pin */
		break;
		case 7:
		SYSCFG->EXTICR[7] |= (SYSCFG_EXTICR2_EXTI7 & SYSCFG_EXTICR2_EXTI7_PB);	/*!< PB[7] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR3 register  **************/
		case 8:
		SYSCFG->EXTICR[8] |= (SYSCFG_EXTICR3_EXTI8 & SYSCFG_EXTICR3_EXTI8_PB);	/*!< PB[8] pin */
		break;
		case 9:
		SYSCFG->EXTICR[9] |= (SYSCFG_EXTICR3_EXTI9 & SYSCFG_EXTICR3_EXTI9_PB);	/*!< PB[9] pin */
		break;
		case 10:
		SYSCFG->EXTICR[10] |= (SYSCFG_EXTICR3_EXTI10 & SYSCFG_EXTICR3_EXTI10_PB);	/*!< PB[10] pin */
		break;
		case 11:
		SYSCFG->EXTICR[11] |= (SYSCFG_EXTICR3_EXTI11 & SYSCFG_EXTICR3_EXTI11_PB);	/*!< PB[11] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR4 register  **************/
		case 12:
		SYSCFG->EXTICR[12] |= (SYSCFG_EXTICR4_EXTI12 & SYSCFG_EXTICR4_EXTI12_PB);	/*!< PB[12] pin */
		break;
		case 13:
		SYSCFG->EXTICR[13] |= (SYSCFG_EXTICR4_EXTI13 & SYSCFG_EXTICR4_EXTI13_PB);	/*!< PB[13] pin */
		break;
		case 14:
		SYSCFG->EXTICR[14] |= (SYSCFG_EXTICR4_EXTI14 & SYSCFG_EXTICR4_EXTI14_PB);	/*!< PB[14] pin */
		break;
		case 15:
		SYSCFG->EXTICR[15] |= (SYSCFG_EXTICR4_EXTI15 & SYSCFG_EXTICR4_EXTI15_PB);	/*!< PB[15] pin */
		break;
		}
	}

	/*****************  PORTC configuration for SYSCFG_EXTICRx  **************/
	if(PORT == GPIOC)
	{
		switch(pin)
		{
		/*****************  Bit configuration for SYSCFG_EXTICR1 register  **************/
		case 0:
		SYSCFG->EXTICR[0] |= (SYSCFG_EXTICR1_EXTI0 & SYSCFG_EXTICR1_EXTI0_PC);	/*!< PC[0] pin */
		break;
		case 1:
		SYSCFG->EXTICR[1] |= (SYSCFG_EXTICR1_EXTI1 & SYSCFG_EXTICR1_EXTI1_PC);	/*!< PC[1] pin */
		break;
		case 2:
		SYSCFG->EXTICR[2] |= (SYSCFG_EXTICR1_EXTI2 & SYSCFG_EXTICR1_EXTI2_PC);	/*!< PC[2] pin */
		break;
		case 3:
		SYSCFG->EXTICR[3] |= (SYSCFG_EXTICR1_EXTI3 & SYSCFG_EXTICR1_EXTI3_PC);	/*!< PC[3] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR2 register  **************/
		case 4:
		SYSCFG->EXTICR[4] |= (SYSCFG_EXTICR2_EXTI4 & SYSCFG_EXTICR2_EXTI4_PC);	/*!< PC[4] pin */
		break;
		case 5:
		SYSCFG->EXTICR[5] |= (SYSCFG_EXTICR2_EXTI5 & SYSCFG_EXTICR2_EXTI5_PC);	/*!< PC[5] pin */
		break;
		case 6:
		SYSCFG->EXTICR[6] |= (SYSCFG_EXTICR2_EXTI6 & SYSCFG_EXTICR2_EXTI6_PC);	/*!< PC[6] pin */
		break;
		case 7:
		SYSCFG->EXTICR[7] |= (SYSCFG_EXTICR2_EXTI7 & SYSCFG_EXTICR2_EXTI7_PC);	/*!< PC[7] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR3 register  **************/
		case 8:
		SYSCFG->EXTICR[8] |= (SYSCFG_EXTICR3_EXTI8 & SYSCFG_EXTICR3_EXTI8_PC);	/*!< PC[8] pin */
		break;
		case 9:
		SYSCFG->EXTICR[9] |= (SYSCFG_EXTICR3_EXTI9 & SYSCFG_EXTICR3_EXTI9_PC);	/*!< PC[9] pin */
		break;
		case 10:
		SYSCFG->EXTICR[10] |= (SYSCFG_EXTICR3_EXTI10 & SYSCFG_EXTICR3_EXTI10_PC);	/*!< PC[10] pin */
		break;
		case 11:
		SYSCFG->EXTICR[11] |= (SYSCFG_EXTICR3_EXTI11 & SYSCFG_EXTICR3_EXTI11_PC);	/*!< PC[11] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR4 register  **************/
		case 12:
		SYSCFG->EXTICR[12] |= (SYSCFG_EXTICR4_EXTI12 & SYSCFG_EXTICR4_EXTI12_PC);	/*!< PC[12] pin */
		break;
		case 13:
		SYSCFG->EXTICR[13] |= (SYSCFG_EXTICR4_EXTI13 & SYSCFG_EXTICR4_EXTI13_PC);	/*!< PC[13] pin */
		break;
		case 14:
		SYSCFG->EXTICR[14] |= (SYSCFG_EXTICR4_EXTI14 & SYSCFG_EXTICR4_EXTI14_PC);	/*!< PC[14] pin */
		break;
		case 15:
		SYSCFG->EXTICR[15] |= (SYSCFG_EXTICR4_EXTI15 & SYSCFG_EXTICR4_EXTI15_PC);	/*!< PC[15] pin */
		break;
		}
	}

	/*****************  PORTD configuration for SYSCFG_EXTICRx  **************/
	if(PORT == GPIOD)
	{
		switch(pin)
		{
		/*****************  Bit configuration for SYSCFG_EXTICR1 register  **************/
		case 0:
		SYSCFG->EXTICR[0] |= (SYSCFG_EXTICR1_EXTI0 & SYSCFG_EXTICR1_EXTI0_PD);	/*!< PD[0] pin */
		break;
		case 1:
		SYSCFG->EXTICR[1] |= (SYSCFG_EXTICR1_EXTI1 & SYSCFG_EXTICR1_EXTI1_PD);	/*!< PD[1] pin */
		break;
		case 2:
		SYSCFG->EXTICR[2] |= (SYSCFG_EXTICR1_EXTI2 & SYSCFG_EXTICR1_EXTI2_PD);	/*!< PD[2] pin */
		break;
		case 3:
		SYSCFG->EXTICR[3] |= (SYSCFG_EXTICR1_EXTI3 & SYSCFG_EXTICR1_EXTI3_PD);	/*!< PD[3] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR2 register  **************/
		case 4:
		SYSCFG->EXTICR[4] |= (SYSCFG_EXTICR2_EXTI4 & SYSCFG_EXTICR2_EXTI4_PD);	/*!< PD[4] pin */
		break;
		case 5:
		SYSCFG->EXTICR[5] |= (SYSCFG_EXTICR2_EXTI5 & SYSCFG_EXTICR2_EXTI5_PD);	/*!< PD[5] pin */
		break;
		case 6:
		SYSCFG->EXTICR[6] |= (SYSCFG_EXTICR2_EXTI6 & SYSCFG_EXTICR2_EXTI6_PD);	/*!< PD[6] pin */
		break;
		case 7:
		SYSCFG->EXTICR[7] |= (SYSCFG_EXTICR2_EXTI7 & SYSCFG_EXTICR2_EXTI7_PD);	/*!< PD[7] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR3 register  **************/
		case 8:
		SYSCFG->EXTICR[8] |= (SYSCFG_EXTICR3_EXTI8 & SYSCFG_EXTICR3_EXTI8_PD);	/*!< PD[8] pin */
		break;
		case 9:
		SYSCFG->EXTICR[9] |= (SYSCFG_EXTICR3_EXTI9 & SYSCFG_EXTICR3_EXTI9_PD);	/*!< PD[9] pin */
		break;
		case 10:
		SYSCFG->EXTICR[10] |= (SYSCFG_EXTICR3_EXTI10 & SYSCFG_EXTICR3_EXTI10_PD);	/*!< PD[10] pin */
		break;
		case 11:
		SYSCFG->EXTICR[11] |= (SYSCFG_EXTICR3_EXTI11 & SYSCFG_EXTICR3_EXTI11_PD);	/*!< PD[11] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR4 register  **************/
		case 12:
		SYSCFG->EXTICR[12] |= (SYSCFG_EXTICR4_EXTI12 & SYSCFG_EXTICR4_EXTI12_PD);	/*!< PD[12] pin */
		break;
		case 13:
		SYSCFG->EXTICR[13] |= (SYSCFG_EXTICR4_EXTI13 & SYSCFG_EXTICR4_EXTI13_PD);	/*!< PD[13] pin */
		break;
		case 14:
		SYSCFG->EXTICR[14] |= (SYSCFG_EXTICR4_EXTI14 & SYSCFG_EXTICR4_EXTI14_PD);	/*!< PD[14] pin */
		break;
		case 15:
		SYSCFG->EXTICR[15] |= (SYSCFG_EXTICR4_EXTI15 & SYSCFG_EXTICR4_EXTI15_PD);	/*!< PD[15] pin */
		break;
		}
	}

	/*****************  PORTF configuration for SYSCFG_EXTICRx  **************/
	if(PORT == GPIOF)
	{
		switch(pin)
		{
		/*****************  Bit configuration for SYSCFG_EXTICR1 register  **************/
		case 0:
		SYSCFG->EXTICR[0] |= (SYSCFG_EXTICR1_EXTI0 & SYSCFG_EXTICR1_EXTI0_PF);	/*!< PF[0] pin */
		break;
		case 1:
		SYSCFG->EXTICR[1] |= (SYSCFG_EXTICR1_EXTI1 & SYSCFG_EXTICR1_EXTI1_PF);	/*!< PF[1] pin */
		break;
		case 2:
		SYSCFG->EXTICR[2] |= (SYSCFG_EXTICR1_EXTI2 & SYSCFG_EXTICR1_EXTI2_PF);	/*!< PF[2] pin */
		break;
		case 3:
		SYSCFG->EXTICR[3] |= (SYSCFG_EXTICR1_EXTI3 & SYSCFG_EXTICR1_EXTI3_PF);	/*!< PF[3] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR2 register  **************/
		case 4:
		SYSCFG->EXTICR[4] |= (SYSCFG_EXTICR2_EXTI4 & SYSCFG_EXTICR2_EXTI4_PF);	/*!< PF[4] pin */
		break;
		case 5:
		SYSCFG->EXTICR[5] |= (SYSCFG_EXTICR2_EXTI5 & SYSCFG_EXTICR2_EXTI5_PF);	/*!< PF[5] pin */
		break;
		case 6:
		SYSCFG->EXTICR[6] |= (SYSCFG_EXTICR2_EXTI6 & SYSCFG_EXTICR2_EXTI6_PF);	/*!< PF[6] pin */
		break;
		case 7:
		SYSCFG->EXTICR[7] |= (SYSCFG_EXTICR2_EXTI7 & SYSCFG_EXTICR2_EXTI7_PF);	/*!< PF[7] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR3 register  **************/
		case 8:
		SYSCFG->EXTICR[8] |= (SYSCFG_EXTICR3_EXTI8 & SYSCFG_EXTICR3_EXTI8_PF);	/*!< PF[8] pin */
		break;
		case 9:
		SYSCFG->EXTICR[9] |= (SYSCFG_EXTICR3_EXTI9 & SYSCFG_EXTICR3_EXTI9_PF);	/*!< PF[9] pin */
		break;
		case 10:
		SYSCFG->EXTICR[10] |= (SYSCFG_EXTICR3_EXTI10 & SYSCFG_EXTICR3_EXTI10_PF);	/*!< PF[10] pin */
		break;
		case 11:
		SYSCFG->EXTICR[11] |= (SYSCFG_EXTICR3_EXTI11 & SYSCFG_EXTICR3_EXTI11_PF);	/*!< PF[11] pin */
		break;
		/*****************  Bit configuration for SYSCFG_EXTICR4 register  **************/
		case 12:
		SYSCFG->EXTICR[12] |= (SYSCFG_EXTICR4_EXTI12 & SYSCFG_EXTICR4_EXTI12_PF);	/*!< PF[12] pin */
		break;
		case 13:
		SYSCFG->EXTICR[13] |= (SYSCFG_EXTICR4_EXTI13 & SYSCFG_EXTICR4_EXTI13_PF);	/*!< PF[13] pin */
		break;
		case 14:
		SYSCFG->EXTICR[14] |= (SYSCFG_EXTICR4_EXTI14 & SYSCFG_EXTICR4_EXTI14_PF);	/*!< PF[14] pin */
		break;
		case 15:
		SYSCFG->EXTICR[15] |= (SYSCFG_EXTICR4_EXTI15 & SYSCFG_EXTICR4_EXTI15_PF);	/*!< PF[15] pin */
		break;
		}
	}

	/*****************  Rising/Falling Trigger configuration register  **************/
	if(edge == RISING_EDGE){
		EXTI->RTSR |= 1<<pin;
	}
	if(edge == FALLING_EDGE){
		EXTI->FTSR |= 1<<pin;
	}
	if(edge == RISING_FALLING_EDGE){
		EXTI->RTSR |= 1<<pin;
		EXTI->FTSR |= 1<<pin;
	}
}

void enable_gpio_interrupt(uint32_t pin, IRQn_Type irqNum, uint8_t setPriority)
{
	/*****************  Interrupt mask configuration register  **************/
	EXTI->IMR |= 1<<pin;
	/*****************  Interrupt NVIC SetPriority configuration register  **************/
	NVIC_SetPriority(irqNum, setPriority);
	/*****************  Interrupt NVIC irqNum configuration register  **************/
	NVIC_EnableIRQ(irqNum);
}

void reset_interrupt(uint32_t pin)
{
	/*****************  Interrupt Reset configuration register  **************/
	EXTI->PR |= 1<<pin;
}

//*****************************************************************************
//              General-Purpose TIM4 Register CONFIG
void CMR_TIM4_config(TIM_TypeDef *TIMx, uint16_t PSC_val, uint16_t ARR_val, uint8_t direction, uint8_t CMS_mode, IRQn_Type irqNum)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;		// TIM4 clock enable register
	TIMx->CR1 |= TIM_CR1_CEN;				// Enable counter
	TIMx->DIER |= TIM_DIER_UIE;				// Update interrupt enable
	TIMx->EGR |= TIM_EGR_UG;
	TIMx->CR1 |= TIM_CR1_ARPE;				// Auto-reload preload enable

	// fclk = 16Mhz
	//PWM frquency = fclk/ARR/PSC
	//PWM Duty Cycle = CCR4/ARR
	TIMx->PSC = PSC_val-1;					// prescaler
	TIMx->ARR = ARR_val-1;					// auto-reload register. Controls frequency of PWM.
	TIMx->CNT = 0;							// Reset counter
	TIMx->CR1 |= direction;					// Direction
	TIMx->CR1 |= CMS_mode;					// Center-aligned mode selection
	NVIC_EnableIRQ(irqNum);					// Interrupt NVIC irqNum configuration register
}

void CCM_TIM4_config()
{
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_1;
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_2;
	TIM4->CCMR2 |= TIM_CCMR2_OC4PE;
	TIM4->CCR4 = 7500; //for 75%			// Capture/Compare 4 Value. Controls duty cycle of the PWM.
	TIM4->CCER |= TIM_CCER_CC4E;			// Capture/compare 4 interrupt enable
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
