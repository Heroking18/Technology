/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "library.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
# define UART_INT 1000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
enum direction{
	LEFT,
	RIGHT,
};
# define RAND_LIMIT 2
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
int UART_transmit(int);
HAL_StatusTypeDef read_status();

int32_t distance = 0;
uint64_t last_transmit_UART = 0;

// servo values after PID added
double left_wheel = 0;
double right_wheel = 0;

// servo current values
uint32_t left_val = 0;
uint32_t right_val = 0;

// PID simulated values
double KP = 1.0001;
double KI = 0.1825;
double KD = 0.1887;

// PID function variables
double calcpid = 0;
double PID_output = 0;
double prev_error = 0;
double derivative = 0;
int set_point = 50;	// 20cm
int error = 0;
uint8_t rxChar;

// Ultrasonic wall distance function
bool no_wall(uint32_t distance)
{
	return ((distance > 2) &&(distance <= 6));
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int UART_transmit(int value)
{
	char txBuf[80] = {0};
	USART1->ICR |= USART_ICR_ORECF; // Clear the overrun error bit.
	snprintf(txBuf, sizeof(txBuf), " %d\n", value);
	HAL_StatusTypeDef status;
	status = HAL_UART_Transmit(&huart1, (uint8_t *)txBuf, strlen(txBuf), 10);
	return status;
}

HAL_StatusTypeDef read_status()
{
	USART1->ICR |= USART_ICR_ORECF; // Clear the overrun error bit.
	HAL_StatusTypeDef status;
	// Set timeout to 0 so it will not block,
	// just read one character if available.
	status = HAL_UART_Receive(&huart1, (uint8_t*)&rxChar, 1, 0);//IT(&huart3, &rxChar, 1);
	return status;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	RCC->AHBENR|= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;			// Enable GPIO bus
	SetPin(GPIOB, 3, ALTFUNCTMODE, PUSHPULL, LOWSPEED, NOPULL);		// (PB3)D3 Timer 2 PIN Config LEFT WHEEL
	SetPin(GPIOA, 0, ALTFUNCTMODE, PUSHPULL, LOWSPEED, NOPULL);		// (PA0)A0 Timer 2 PIN Config RIGHT WHEEL
	SetPin(GPIOA, 5, OUTPUT, PUSHPULL, LOWSPEED, NOPULL);			// LED test

	CMR_TIM2_config();												// Timer 2 SERVO Config

	SetPin(GPIOB, 5, ALTFUNCTMODE, PUSHPULL, LOWSPEED, NOPULL);		// (PB5)D4 Timer 3 TRIGGER Config
	CMR_TIM3_config();												// Timer 3 TRIGGER Config

	SetPin(GPIOB, 6, ALTFUNCTMODE, PUSHPULL, LOWSPEED, NOPULL);		// (PB6)D10 Timer 4 ECHO Config
	CMR_TIM4_config();												// Timer 4 ECHO Config
  INIT_RAND(RAND_LIMIT);
  urand_t rand_direction = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  distance = ((TIM4->CCR2)/58);
	  distance -= 38;

	  if(HAL_GetTick() - last_transmit_UART >= UART_INT)
	  {
		  last_transmit_UART = HAL_GetTick();
		  UART_transmit(distance);
	  }

	  if(read_status() == HAL_OK)
	  {
		  set_point = rxChar;
	  }

	  PID_output = myPID(distance, set_point, KP, KD);
	  left_wheel = map(PID_output, 0, 100, 178, 187);	// Used to map servo speed into 0 to 100%
	  right_wheel = map(PID_output, 0, 100, 162, 151);
	if (no_wall(distance))	// condition activates when it reaches 10cm
	{
		servo_pwm(0, 0);				// first param left wheel PB3. second param right wheel PA0. (FULLSTOP)
		HAL_Delay(1000);

		// Good shit
		rand_direction = Get_Random_NoU();
		// Now use this shit of a random generated direction no
		switch (rand_direction) {
			case LEFT:{
				// Put code to move to the left
				servo_pwm(151, 0);
				HAL_Delay(1250);
				servo_pwm(0, 151);				// first param left wheel PB3. second param right wheel PA0. (TURN LEFT)
				break;
			}
			case RIGHT:{
				// Put the code to move to the right
				servo_pwm(0, 187);
				HAL_Delay(1250);
				servo_pwm(187, 0);				// first param left wheel PB3. second param right wheel PA0. (TURN RIGHT)
				break;
			}
		}
	}
	else if (no_wall(distance) == false)
	{
		servo_pwm(left_wheel, right_wheel);		// first param left wheel PB3. second param right wheel PA0. (STRAIGHT)
	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }


  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	  /** Initializes the RCC Oscillators according to the specified parameters
	  * in the RCC_OscInitTypeDef structure.
	  */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  /** Initializes the CPU, AHB and APB buses clocks
	  */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
	  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

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
