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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

//*****************************************************************************
//                         Register settings for GPIO
void SetMode(GPIO_TypeDef * PORT, uint8_t pin, uint8_t mode){
	PORT->MODER &= ~(0x3UL << (pin * 2)); // Times 2 because register occupies 2 bits for each MODER.
	PORT->MODER |= (mode << (pin * 2)); // Times 2 because register occupies 2 bits for each MODER.
}

void SetType(GPIO_TypeDef * PORT, uint8_t pin, uint8_t type){
	PORT->OTYPER &= ~(type << pin);
	PORT->OTYPER |= (type << pin);
}

void SetSpeed(GPIO_TypeDef * PORT, uint8_t pin, uint8_t speed){
	PORT->OSPEEDR &= ~(0x3UL << (pin * 2));
	PORT->OSPEEDR |= (speed << (pin * 2));
}

void SetPullType(GPIO_TypeDef * PORT, uint8_t pin, uint8_t pulltype){
	PORT->PUPDR &= ~(0x3UL << (pin * 2));
	PORT->PUPDR |= (pulltype << (pin * 2));
}

void SetPin(GPIO_TypeDef * PORT, uint8_t pin, uint8_t mode, uint8_t type, uint8_t speed, uint8_t pulltype){
	SetMode(PORT, pin, mode);
	SetType(PORT, pin, type);
	SetSpeed(PORT, pin, speed);
	SetPullType(PORT, pin, pulltype);
}

//*****************************************************************************
//						   Function for changing the PWM value
void servo_pwm(uint32_t left_val, uint32_t right_val)
{
  	TIM2->CCR2 = left_val;						// Capture/Compare 2 Value. Controls duty cycle of the PWM. PB3
  	TIM2->CCR1 = right_val;						// Capture/Compare 1 Value. Controls duty cycle of the PWM. PA0
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int myPID(uint32_t sensor_value, int set_point, double kp, double kd)
{

	error = sensor_value - set_point;
	calcpid = (kp * error) + (kd * derivative);
	if(error == 0)
	{
		calcpid = 0;
	}
	prev_error = error;
	return calcpid;
}

//*****************************************************************************
//						   Code for both servo motor
//                         TIM2 Register CONFIG
void CMR_TIM2_config(void)
{
	RCC->APB1ENR = (RCC->APB1ENR & ~RCC_APB1ENR_TIM2EN) | RCC_APB1ENR_TIM2EN; //Enable Timer 2
	TIM2->CR1 |= TIM_CR1_CEN;				// Enable counter
	GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFRL3) | (0b0001 << GPIO_AFRL_AFRL3_Pos);		// GPIO alternate function low register
	GPIOA->AFR[0] = (GPIOA->AFR[0] & ~GPIO_AFRL_AFRL0) | (0b0001 << GPIO_AFRL_AFRL0_Pos);		// GPIO alternate function low register

	// fclk = 16Mhz
	// PWM frequency = fclk/ARR/PSC
	// PWM Duty Cycle = CCR2/ARR
	TIM2->PSC = 320-1;					// prescaler
	TIM2->ARR = 1000-1;					// auto-reload register. Controls frequency of PWM. ARR set to 50hz (20ms)
	TIM2->CNT = 0;						// Reset counter

	TIM2->CCER |= TIM_CCER_CC2E;		// Capture/compare 2 interrupt enable
	TIM2->CCER |= TIM_CCER_CC1E;		// Capture/compare 1 interrupt enable

	TIM2->CR1 |= TIM_CR1_CMS_0;			// Center-aligned mode 1. The counter counts up and down alternatively.

	// PWM mode 1 channel 2 left wheel
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_1;	// Bit 1
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_2;	// Bit 2
	TIM2->CCMR1 |= TIM_CCMR1_OC2PE;		// Output Compare 2 Preload enable

	// PWM mode 1 channel 1 right wheel
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1;	// Bit 1
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_2;	// Bit 2
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE;		// Output Compare 1 Preload enable
}

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
	TIM3->CCR2 = 12;					// 8-12 microsecond pulses

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

void CMR_TIM4_config(void)
{
	// Step 1: Enable timer clock in RCC_APB1ENR or RCC_APB2ENR register.
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;					// bit reset
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;						// TIM4 clock enable register

		//Select alternate function AF2 for GPIO pin PB6.
		GPIOB->AFR[0] =(GPIOB->AFR[0] & ~GPIO_AFRL_AFRL6) | (GPIO_AF2_TIM4 << GPIO_AFRL_AFRL6_Pos);

	// Step 2: Set prescaler register (TIMx_PSC)
	// fclk = 16Mhz
	// PWM frequency = fclk/ARR/PSC
	// PWM Duty Cycle = CCR2/ARR
	TIM4->PSC = 16-1;										// prescaler
	TIM4->ARR = 0xFFFF-1;									// auto-reload register.
	TIM4->CNT = 0;											// Reset counter

	/////////////////////////////////////////////////////// ChANNEL 1
		//Reset register
		TIM4->CCMR1 &= ~TIM4->CCMR1;

		//Filter mode: No filter, sampling is done at fDTS
		TIM4->CCMR1 &= ~TIM_CCMR1_IC1F;

		//Disable PSC for input capture
		TIM4->CCMR1 &= ~TIM_CCMR1_IC1PSC;

		//Set capture/compare as input mode

		TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;
		TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_1;

		//Enable capture compare Channel 1
		TIM4->CCER |= TIM_CCER_CC1E;

		//Set capture compare Channel 1 1 to non-inverted/rising edge
		TIM4->CCER &= ~TIM_CCER_CC1P;
		TIM4->CCER &= ~TIM_CCER_CC1NP;

		///////////////////////////////////////////////////////////////////////////////CHANNEL 2

		//Filter mode: No filter, sampling is done at fDTS
		TIM4->CCMR1 &= ~TIM_CCMR1_IC2F;

		//Disable PSC for input capture
		TIM4->CCMR1 &= ~TIM_CCMR1_IC2PSC;

		//Set capture/compare as input mode (channel is configured as input, IC2 is mapped on TI1.)
		TIM4->CCMR1 &= ~TIM_CCMR1_CC2S_0;
		TIM4->CCMR1 |= TIM_CCMR1_CC2S_1;

		//Enable capture compare Channel 1
		TIM4->CCER |= TIM_CCER_CC2E;

		//Set capture compare Channel 2 inverted/falling edge
		TIM4->CCER = (TIM4->CCER & ~TIM_CCER_CC2P) | TIM_CCER_CC2P;
		TIM4->CCER = (TIM4->CCER & ~TIM_CCER_CC2NP);

	//CONFIG TIMER
		TIM4->SMCR = (TIM4->SMCR & ~TIM_SMCR_TS) | (0b101 << TIM_SMCR_TS_Pos);
		TIM4->SMCR = (TIM4->SMCR & ~TIM_SMCR_SMS) | (0b0100 << TIM_SMCR_SMS_Pos);

		//ENABLE Timer
		TIM4->CR1 |= TIM_CR1_CEN; //Enable TIM4

}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
