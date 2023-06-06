/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  * @name			: Andre Sanao
  * @subject		: Embedded Systems
  * @course			: Technology Semester 3
  ******************************************************************************
  * @summary
  *
  * The objective of this assignment is to create a delay function
  * using system timer. In part A of the assignment, is to create functions for
  * the initialization of the SysTick, Delay and for the LED configurations.
  * The application should toggle an LED every 1 sec using only the Delay function
  * and the Counter Flag bit.
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SysTick_CTRL_CLKSOURCE 0x4UL
#define SysTick_CTRL_TICKINT   0x2UL
#define SysTick_CTRL_ENABLE    0x1UL
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

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

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile int32_t nTime = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void SysTick_Init(uint32_t);
void Delay(uint32_t);
void SetMode(GPIO_TypeDef *, uint8_t, uint8_t);
void SetType(GPIO_TypeDef *, uint8_t, uint8_t);
void SetSpeed(GPIO_TypeDef *, uint8_t, uint8_t);
void SetPullType(GPIO_TypeDef *, uint8_t, uint8_t);
void SetPin(GPIO_TypeDef *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	SysTick_Init(16000);
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; //enable the bus for port B.

	// Pin Configurations.
	SetPin(GPIOB, 5, OUTPUT, PUSHPULL, LOWSPEED, NOPULL); // (PB5) LED1

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
//  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

	  // Toggling LED
		  GPIOB->BSRR |= GPIO_BSRR_BS_5;
		  Delay(500);
		  GPIOB->BSRR |= GPIO_BSRR_BR_5;
		  Delay(500);

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


void SysTick_Init(uint32_t ticks){
	SysTick->CTRL = 0;			// Disable SysTick
	SysTick->LOAD = ticks - 1;  // Set reload register

    SysTick->VAL = 0;             // Reset the SysTick counter value. Software should always clear during the initialization.

    // Select processor clock: 1 = processor clock; 0 = external clock
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;

    // Enables SysTick interrupt, 1 = Enable, 0 = Disable
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT;

    // Enable SysTick
    SysTick->CTRL |= SysTick_CTRL_ENABLE;
}

void Delay(uint32_t nTime){ // Delay in ms
	// nTime: Length of delay time
	// the Delay function initializes the TimeDelay variable, and waits until TimeDelay is decremented to nTime.
	volatile int32_t TimeDelay = 0;

    while(TimeDelay != nTime) // Increment TimeDelay until equal to nTime
    {
        if(SysTick->CTRL & 1UL<<16) // Checks if Counter Flag bit is set to 1, increment TimeDelay by 1
      {
        TimeDelay++;
      }
    }
}

// Register settings for GPIO
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

/* USER CODE BEGIN 4 */

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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
