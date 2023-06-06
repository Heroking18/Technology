/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : library.c
  * @brief          : Private library
  * @name			: Andre Sanao
  * @subject		: Embedded Systems
  * @course			: Technology Semester 3
  ******************************************************************************
  * @summary
  * This file contains functions definitions that will be used during the Semester 3
  * assignments and will be configured to the assignments requirements.
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
volatile uint32_t previous_button_time = 0;
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
	PORT->MODER &= ~(MASK << (pin * 2)); // bit reset
	PORT->MODER |= (mode << (pin * 2)); // Times 2 because register occupies 2 bits for each MODER.
}

void SetType(GPIO_TypeDef * PORT, uint8_t pin, uint8_t type){
	PORT->OTYPER &= ~(type << pin);
	PORT->OTYPER |= (type << pin);
}

void SetSpeed(GPIO_TypeDef * PORT, uint8_t pin, uint8_t speed){
	PORT->OSPEEDR &= ~(MASK << (pin * 2));
	PORT->OSPEEDR |= (speed << (pin * 2));
}

void SetPullType(GPIO_TypeDef * PORT, uint8_t pin, uint8_t pulltype){
	PORT->PUPDR &= ~(MASK << (pin * 2));
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
//                         TIM4 Register CONFIG
void CMR_TIM4_config(void)
{
	// Step 1: Enable timer clock in RCC_APB1ENR or RCC_APB2ENR register.
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;					// bit reset
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;						// TIM4 clock enable register

	// Step 2: Set prescaler register (TIMx_PSC)
	// fclk = 16Mhz
	// PWM frequency = fclk/ARR/PSC
	// PWM Duty Cycle = CCR2/ARR
	TIM4->PSC = 16-1;										// prescaler
	TIM4->ARR = 0xFFFF-1;									// auto-reload register.
	TIM4->CNT = 0;											// Reset counter

	// PWM mode 1
	// Step 3: Set CC1 channel as input with “IC1 mapped on TI1” (TIMx_CCMR1).
	TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_0;						// bit reset
	TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;						// Bit 1. Set CC1 channel as input with “IC1 mapped on TI1”.

	// Step 4: Set CC1NP/CC1P bits to “noninverted / rising edge (TIMx_CCER).
	TIM4->CCER &= ~TIM_CCER_CC1P;							// bit reset
	TIM4->CCER |= ~TIM_CCER_CC1P;							// 00: noninverted/rising edge

	TIM4->CCER &= ~TIM_CCER_CC1NP;							// bit reset
	TIM4->CCER |= TIM_CCER_CC1NP;							// Capture/Compare 1 Complementary output Polarity

	// Step 5: Enable Capture/Compare 1 output (TIMx_CCER).
	TIM4->CCER &= ~TIM_CCER_CC1E; 							// bit reset
	TIM4->CCER |= TIM_CCER_CC1E; 							// Capture/Compare 1 output enable

	// Step 6: Set CC2 channel as input with IC2 mapped on TI1 (TIMx_CCMR1).
	TIM4->CCMR1 &= ~TIM_CCMR1_CC2S_1; 						// bit reset
	TIM4->CCMR1 |= TIM_CCMR1_CC2S_1; 						// 10: CC2 channel is configured as input, IC2 is mapped on TI1

	// Step 7: Set CC2NP/CC2P bits to inverted / falling edge (TIMx_CCER).
	TIM4->CCER &= ~TIM_CCER_CC1NP; 							// bit reset
	TIM4->CCER |= TIM_CCER_CC1NP; 							// Refer to CC1NP description

	TIM4->CCER &= ~TIM_CCER_CC1P; 							// bit reset
	TIM4->CCER |= TIM_CCER_CC1P; 							// 01: inverted/falling edge

	// Step 8: Enable Capture/Compare 2 output (TIMx_CCER).
	TIM4->CCER &= ~TIM_CCER_CC2E;							// bit reset
	TIM4->CCER |= TIM_CCER_CC2E;							// Capture/Compare 2 output enable

	// Step 9: Set Trigger selection to Filtered Timer Input 1 (TIMx_SMCR).
	TIM4->SMCR &= ~(TIM_SMCR_TS_0 | TIM_SMCR_TS_2); 		// bit reset
	TIM4->SMCR |= (TIM_SMCR_TS_0 | TIM_SMCR_TS_2); 			// 101: Filtered Timer Input 1 (TI1FP1)

	// Step 10: Set Slave mode selection to Reset Mode (TIMx_SMCR).
	TIM4->SMCR &= ~TIM_SMCR_SMS_2;							// bit reset
	TIM4->SMCR |= TIM_SMCR_SMS_2;							// 0100: Reset Mode - Rising edge of the selected trigger input (TRGI) reinitializes the counter
															// and generates an update of the registers.

	// Step 11: Enable counter (TIMx_CR1).
	TIM4->CR1 &= ~TIM_CR1_CEN;								// bit reset
	TIM4->CR1 |= TIM_CR1_CEN;								// 1: Counter enabled

	// Step 12: Connect timer channel 1 input to a GPIO pin by setting an alternate function for that pin, see later in this presentation.
	GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFRL6) | (0b0010 << GPIO_AFRL_AFRL6_Pos);	// GPIO alternate function low register. PB6 TIM4_CH1 AFR6 AF2

	// Enabling timer 4 capture/compare interrupt
	NVIC_EnableIRQ(TIM4_IRQn); 								// Enable interrupt vector
	TIM4->DIER &= ~TIM_DIER_CC1IE; 							// bit reset
	TIM4->DIER |= TIM_DIER_CC1IE; 							// Capture/compare 1 interrupt enable

}

//*****************************************************************************
//                         TIM3 Register CONFIG
void CMR_TIM3_config(void)
{
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN;	// reset bit
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;		// TIM3 clock enable register

	GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFRL5) | (0b0010 << GPIO_AFRL_AFRL5_Pos);		// GPIO alternate function low register

	// fclk = 16Mhz
	// PWM frequency = fclk/ARR/PSC
	// PWM Duty Cycle = CCR2/ARR
	TIM3->PSC = 16-1;					// prescaler 1MHz
	TIM3->ARR = 0xFFFF-1;				// auto-reload register.
	TIM3->CNT = 0;						// Reset counter
	TIM3->CCR2 = 11;					// 8-12 microsecond pulses

	TIM3->CCER &= ~TIM_CCER_CC2E;		// reset bit
	TIM3->CCER |= TIM_CCER_CC2E;		// Capture/compare 2 interrupt enable

	TIM3->CCMR1 &= ~TIM_CCMR1_CC2S;		// reset bit
	TIM3->CCMR1 |= TIM_CCMR1_CC2S;		// 00: CC2 channel is configured as output

	// PWM mode 1 Channel 2
	// Output Compare 2 mode
	TIM3->CCMR1 &= ~TIM_CCMR1_OC2M_0;	// Bit 0

	TIM3->CCMR1 &= ~TIM_CCMR1_OC2M_1;	// reset bit
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_1;	// Bit 1

	TIM3->CCMR1 &= ~TIM_CCMR1_OC2M_2;	// reset bit
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_2;	// Bit 2

	TIM3->CCMR1 &= ~TIM_CCMR1_OC2M_3;	// Bit 3

	TIM3->CCMR1 &= ~TIM_CCMR1_OC2PE;	// reset bit
	TIM3->CCMR1 |= TIM_CCMR1_OC2PE;		// Output Compare 2 Preload enable

	TIM3->CR1 &= ~TIM_CR1_CEN;	 			// reset bit
	TIM3->CR1 |= TIM_CR1_CEN;	 			// Enable counter
}

//*****************************************************************************
//                         optional assignment CONFIG
void ultrasonic_sensor_led(void)
{
	if((millis() - previous_button_time) >= 20) //	Debouncing using millis()
	{
	  if (flag)
	  {
		  	flag = 0;

		  	// LEDs will turn on/off at a certain distance.
			if ((distance >= 2) && (distance <= 5))
			{
				GPIOB->BSRR |= GPIO_BSRR_BS_3;
			}
			else if ((distance >= 2) && (distance <= 15))
			{
				GPIOB->BSRR |= GPIO_BSRR_BS_4;
			}
			else if (distance >= 6)
			{
				GPIOB->BSRR |= GPIO_BSRR_BR_3;
				if (distance >= 30)
				{
					GPIOB->BSRR |= GPIO_BSRR_BR_4;
				}
			}
	  }
		previous_button_time = millis(); //	current time will be saved to previous time to reset debouncing
	}
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
