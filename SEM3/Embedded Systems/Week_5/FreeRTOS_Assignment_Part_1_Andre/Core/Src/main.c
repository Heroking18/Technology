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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
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
UART_HandleTypeDef huart2;

/* Definitions for StartTerminal */
osThreadId_t StartTerminalHandle;
const osThreadAttr_t StartTerminal_attributes = {
  .name = "StartTerminal",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for StartScene */
osThreadId_t StartSceneHandle;
const osThreadAttr_t StartScene_attributes = {
  .name = "StartScene",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myQueue01 */
osMessageQueueId_t myQueue01Handle;
const osMessageQueueAttr_t myQueue01_attributes = {
  .name = "myQueue01"
};
/* Definitions for myQueue02 */
osMessageQueueId_t myQueue02Handle;
const osMessageQueueAttr_t myQueue02_attributes = {
  .name = "myQueue02"
};
/* Definitions for BlockSprinkler1 */
osMutexId_t BlockSprinkler1Handle;
const osMutexAttr_t BlockSprinkler1_attributes = {
  .name = "BlockSprinkler1"
};
/* Definitions for BlockScene2 */
osMutexId_t BlockScene2Handle;
const osMutexAttr_t BlockScene2_attributes = {
  .name = "BlockScene2"
};
/* Definitions for BlockScene1 */
osMutexId_t BlockScene1Handle;
const osMutexAttr_t BlockScene1_attributes = {
  .name = "BlockScene1"
};
/* Definitions for BlockScene3 */
osMutexId_t BlockScene3Handle;
const osMutexAttr_t BlockScene3_attributes = {
  .name = "BlockScene3"
};
/* Definitions for BlockSprinkler2 */
osMutexId_t BlockSprinkler2Handle;
const osMutexAttr_t BlockSprinkler2_attributes = {
  .name = "BlockSprinkler2"
};
/* Definitions for BlockSprinkler3 */
osMutexId_t BlockSprinkler3Handle;
const osMutexAttr_t BlockSprinkler3_attributes = {
  .name = "BlockSprinkler3"
};
/* USER CODE BEGIN PV */

enum task_name {
	SPRINKLER1HIGH,
	SPRINKLER2HIGH,
	SPRINKLER3HIGH,
	SPRINKLER1LOW,
	SPRINKLER2LOW,
	SPRINKLER3LOW,
	DELAY,
};

uint8_t Scene1[] = {SPRINKLER1HIGH, DELAY, SPRINKLER1LOW, SPRINKLER2HIGH, DELAY, SPRINKLER2LOW};
uint8_t Scene2[] = {SPRINKLER2HIGH, DELAY, SPRINKLER2LOW, SPRINKLER3HIGH, DELAY, SPRINKLER3LOW};
uint8_t Scene3[] = {SPRINKLER3HIGH, DELAY, SPRINKLER3LOW, SPRINKLER2HIGH, DELAY, SPRINKLER2LOW};

#define ARRAY_SIZE 6

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void Terminal(void *argument);
void execScene(void *argument);

/* USER CODE BEGIN PFP */
//*****************************************************************************
//                             GPIO PIN CONFIG
void SetMode(GPIO_TypeDef *, uint8_t, uint8_t);
void SetType(GPIO_TypeDef *, uint8_t, uint8_t);
void SetSpeed(GPIO_TypeDef *, uint8_t, uint8_t);
void SetPullType(GPIO_TypeDef *, uint8_t, uint8_t);
void SetPin(GPIO_TypeDef *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
osStatus_t BlockSprinkler1;
osStatus_t BlockSprinkler2;
osStatus_t BlockSprinkler3;
osStatus_t BlockScene1;
osStatus_t BlockScene2;
osStatus_t BlockScene3;

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
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 	//enable the bus for port A.
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 	//enable the bus for port B.
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; 	//enable the bus for port C.

	SetPin(GPIOC, 7, OUTPUT, PUSHPULL, LOWSPEED, NOPULL); 	// (PC7) LED0
	SetPin(GPIOB, 5, OUTPUT, PUSHPULL, LOWSPEED, NOPULL); 	// (PB5) LED1
	SetPin(GPIOA, 10, OUTPUT, PUSHPULL, LOWSPEED, NOPULL); 	// (PA10) LED2

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of BlockSprinkler1 */
  BlockSprinkler1Handle = osMutexNew(&BlockSprinkler1_attributes);

  /* creation of BlockScene2 */
  BlockScene2Handle = osMutexNew(&BlockScene2_attributes);

  /* creation of BlockScene1 */
  BlockScene1Handle = osMutexNew(&BlockScene1_attributes);

  /* creation of BlockScene3 */
  BlockScene3Handle = osMutexNew(&BlockScene3_attributes);

  /* creation of BlockSprinkler2 */
  BlockSprinkler2Handle = osMutexNew(&BlockSprinkler2_attributes);

  /* creation of BlockSprinkler3 */
  BlockSprinkler3Handle = osMutexNew(&BlockSprinkler3_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of myQueue01 */
  myQueue01Handle = osMessageQueueNew (1000, sizeof(uint16_t), &myQueue01_attributes);

  /* creation of myQueue02 */
  myQueue02Handle = osMessageQueueNew (1000, sizeof(uint16_t), &myQueue02_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of StartTerminal */
  StartTerminalHandle = osThreadNew(Terminal, NULL, &StartTerminal_attributes);

  /* creation of StartScene */
  StartSceneHandle = osThreadNew(execScene, NULL, &StartScene_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

void Tasks(uint8_t msg_ptr)
{
	osStatus_t status;
	status = osMessageQueueGet(myQueue02Handle, &msg_ptr, 0U, 0U);   // wait for message
		if (status == osOK) {
			switch (msg_ptr) {
				case SPRINKLER1HIGH:
					BlockSprinkler1 = osMutexAcquire(BlockSprinkler1Handle, 0U);

					if (BlockSprinkler1 == osOK)
					GPIOA->BSRR |= GPIO_BSRR_BS_10;
					break;
				case SPRINKLER2HIGH:
					BlockSprinkler2 = osMutexAcquire(BlockSprinkler2Handle, 0U);

					if (BlockSprinkler2 == osOK)
					GPIOB->BSRR |= GPIO_BSRR_BS_5;
					break;
				case SPRINKLER3HIGH:
					BlockSprinkler3 = osMutexAcquire(BlockSprinkler3Handle, 0U);

					if (BlockSprinkler3 == osOK)
					GPIOC->BSRR |= GPIO_BSRR_BS_7;
					break;
				case SPRINKLER1LOW:
					GPIOA->BSRR |= GPIO_BSRR_BR_10;
					BlockSprinkler1 = osMutexRelease(BlockSprinkler1Handle);
					break;
				case SPRINKLER2LOW:
					GPIOB->BSRR |= GPIO_BSRR_BR_5;
					BlockSprinkler2 = osMutexRelease(BlockSprinkler2Handle);
					break;
				case SPRINKLER3LOW:
					GPIOC->BSRR |= GPIO_BSRR_BR_7;
					BlockSprinkler3 = osMutexRelease(BlockSprinkler3Handle);
					break;
				case DELAY:
					osDelay(3000);
					break;
				default:
					osThreadTerminate(NULL);
					break;
			}
		}
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_Terminal */
/**
  * @brief  Function implementing the StartTerminal thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Terminal */
void Terminal(void *argument)
{
  /* USER CODE BEGIN 5 */

	/* Infinite loop */
	for(;;)
	{
		uint8_t rxChar;
		HAL_StatusTypeDef status;
		USART2->ICR |= USART_ICR_ORECF; // Clear the overrun error bit.
		// Set timeout to 0 so it will not block,
		// just read one character if available.
		status = HAL_UART_Receive(&huart2, &rxChar, 1, 0);
		if (status == HAL_OK) // No HAL_TIMEOUT, so a character is read.
		{
			StartSceneHandle = osThreadNew(execScene, &rxChar, &StartScene_attributes);
		}
	}
	osThreadTerminate(NULL);
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_execScene */
/**
* @brief Function implementing the StartScene thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_execScene */
void execScene(void *argument)
{
  /* USER CODE BEGIN execScene */
	char *rxChar = (char*) argument;
	osStatus_t status;
	osMessageQueuePut(myQueue01Handle,&rxChar, 0U, 0U);

	status = osMessageQueueGet(myQueue01Handle, &rxChar, 0U, 0U);   // wait for message
		if (status == osOK) {

			switch (*rxChar) {
				case '1':
					BlockScene1 = osMutexAcquire(BlockScene1Handle, 0U);
					if (BlockScene1 == osOK)  {
						for(uint8_t i = 0; i<ARRAY_SIZE; i++)
						{
							osMessageQueuePut(myQueue02Handle,&Scene1[i], 0U, 0U);
							Tasks(Scene1[i]);
						}
					}
					BlockScene1 = osMutexRelease(BlockScene1Handle);
					break;
				case '2':
					BlockScene2 = osMutexAcquire(BlockScene2Handle, 0U);
					if (BlockScene2 == osOK)  {
						for(uint8_t i = 0; i<ARRAY_SIZE; i++)
						{
							osMessageQueuePut(myQueue02Handle,&Scene2[i], 0U, 0U);
							Tasks(Scene2[i]);
						}
					}
					BlockScene2 = osMutexRelease(BlockScene2Handle);
					break;
				case '3':
					BlockScene3 = osMutexAcquire(BlockScene3Handle, 0U);
					if (BlockScene3 == osOK)  {
						for(uint8_t i = 0; i<ARRAY_SIZE; i++)
						{
							osMessageQueuePut(myQueue02Handle,&Scene3[i], 0U, 0U);
							Tasks(Scene3[i]);
						}
					}
					BlockScene3 = osMutexRelease(BlockScene3Handle);
					break;
				case '4':
					osMessageQueueDelete(myQueue01Handle);
					break;
				default:
					break;
		}
    }
	osThreadExit();
  /* USER CODE END execScene */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
