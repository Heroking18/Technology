/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */
volatile int8_t flag = 0;
volatile uint32_t millis_counter = 0;
volatile int32_t timerCounter = 0;
volatile int8_t flag2 = 0;
volatile int32_t timerCounter2 = 0;
volatile uint32_t previous_button0_time;
volatile uint32_t previous_button1_time;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
//  /* USER CODE BEGIN SysTick_IRQn 0 */

	//	Systick counter incrementations.
	millis_counter++;
	timerCounter++;
	timerCounter2++;
//  /* USER CODE END SysTick_IRQn 0 */

//  /* USER CODE BEGIN SysTick_IRQn 1 */
//
//  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

void Button0_Press()
{
	//	Wait for the interrupt to set the flag and then reset it before taking any action.
	flag = 0;
	if((millis() - previous_button0_time) >= 20) // Debouncing using millis()
	{
		  if((GPIOA->IDR & GPIO_IDR_4) == 0)
		  {
			  timerCounter = 0; //	Resets counter when button is not pressed
	  	  }

		  //	Button toggle depending on how long its pressed
		  if((GPIOA->IDR & GPIO_IDR_4) != 0)
		  {
		  	  if(timerCounter > 500)
		  	  {
			  	  GPIOA->BSRR |= GPIO_BSRR_BR_10;
		  	  }
		  	  else if((timerCounter >= 20) && (timerCounter <= 500))
		  	  {
			  	  GPIOA->BSRR |= GPIO_BSRR_BS_10;
		  	  }
		  	  previous_button0_time = millis(); //	current time will be saved to previous time to reset debouncing
		  }
	}
}

void Button1_Press()
{
	//	Wait for the interrupt to set the flag2 and then reset it before taking any action.
	flag2 = 0;
	if((millis() - previous_button1_time) >= 20) //	Debouncing using millis()
	{
		  if((GPIOB->IDR & GPIO_IDR_0) == 0)
		  {
			  timerCounter2 = 0; //	Resets counter when button is not pressed
	  	  }

		  //	Button toggle depending on how long its pressed
		  if((GPIOB->IDR & GPIO_IDR_0) != 0)
		  {
		  	  if(timerCounter2 > 500)
		  	  {
		  		GPIOB->BSRR |= GPIO_BSRR_BR_5;
		  	  }
		  	  else if(timerCounter2 >= 20 && timerCounter2 <= 500)
		  	  {
		  		GPIOB->BSRR |= GPIO_BSRR_BS_5;
		  	  }
		  }
		previous_button1_time = millis(); //	current time will be saved to previous time to reset debouncing
	}
}

void EXTI4_IRQHandler()
{
	// Reset interrupt flag of EXTI4.
	if(EXTI->PR & EXTI_PR_PR4)
		{
		reset_interrupt(4);
		}
	//	Enable flag when button interrupt occurs
	flag = 1;
	if(flag)
	{
		Button0_Press();
	}
}

void EXTI0_IRQHandler()
{
	// Reset interrupt flag of EXTI0.
	if(EXTI->PR & EXTI_PR_PR0)
		{
		reset_interrupt(0);
		}
	//	Enable flag2 when button interrupt occurs
	flag2 = 1;
	if(flag2)
	{
		Button1_Press();
	}
}
/* USER CODE END 1 */
