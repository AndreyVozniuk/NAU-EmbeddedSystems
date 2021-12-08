/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
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
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

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
		MX_USART1_UART_Init();
		/* USER CODE BEGIN 2 */
		uint32_t SIZE_ONE_PAGE = 0x400; // розмір сторінки 1 Кб, або 1024 байта
		  //uint32_t ADDR_FLASH_PAGE = 0x08000000 + 64 * SIZE_ONE_PAGE; // адреса 64 сторінки 0x0800FC00
		uint32_t ADDR_FLASH_PAGE = 0x08000000 + 31 * SIZE_ONE_PAGE; // адреса 31 сторінки 0x08007C00
		size_t SIZE_uint32 = sizeof(uint32_t); // 32 біта це 4 байти
		// в одну сторінку розміром 1Кб можна записати 1024/4=256 змінних розміром 4 байти

		uint32_t val_000 = 0x01234567;
    	uint32_t val_004 = 0x89ABCDEF;
    	uint32_t val_00C = 0x01020304;
    	uint32_t val_3FC = 0x0000FFFF; //1024-4=1020 == 0x400-0x004=0x3FC

    	HAL_UART_Transmit(&huart1, (uint8_t*)"\n\n\r!!!Erase page 31!!!\n\r", sizeof("\n\n\r!!!Erase page 31!!!\n\r"), 100);
    	Flash_Erase_One_Page(ADDR_FLASH_PAGE); // очищення 31 сторінки

    	HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Write!!!\n\r", sizeof("\n!!!Write!!!\n\r"), 100);
    	// запис значень на початку і в кінці 127 сторінки
    	Flash_Write_uint32(ADDR_FLASH_PAGE + 0 * SIZE_uint32, val_000);
    	Flash_Write_uint32(ADDR_FLASH_PAGE + 1 * SIZE_uint32, val_004);
    	Flash_Write_uint32(ADDR_FLASH_PAGE + 3 * SIZE_uint32, val_00C);
    	Flash_Write_uint32(ADDR_FLASH_PAGE + 255 * SIZE_uint32, val_3FC);

    	HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Erase page 30!!!\n\r", sizeof("\n!!!Erase page 30!!!\n\r"), 100);
    	Flash_Erase_One_Page(ADDR_FLASH_PAGE - SIZE_ONE_PAGE); // очищення 30 сторінки

    	HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Write!!!\n\r", sizeof("\n!!!Write!!!\n\r"), 100);
    	// запис значень на початку і в кінці 126 сторінки
    	Flash_Write_uint32(ADDR_FLASH_PAGE - SIZE_ONE_PAGE + 0x000, val_000);
    	Flash_Write_uint32(ADDR_FLASH_PAGE - SIZE_ONE_PAGE + 0x004, val_004);
    	Flash_Write_uint32(ADDR_FLASH_PAGE - SIZE_ONE_PAGE + 0x00C, val_00C);
    	Flash_Write_uint32(ADDR_FLASH_PAGE - SIZE_ONE_PAGE + 0x3FC, val_3FC);

    	HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Read!!!\n\r", sizeof("\n!!!Read!!!\n\r"), 100);
    	// читання значень з 64 сторінки Flash-пам'яті
    	uint32_t a = Flash_Read_uint32(ADDR_FLASH_PAGE + 0 * SIZE_uint32);
    	uint32_t b = Flash_Read_uint32(ADDR_FLASH_PAGE + 1 * SIZE_uint32);
    	uint32_t c = Flash_Read_uint32(ADDR_FLASH_PAGE + 3 * SIZE_uint32);
    	uint32_t d = Flash_Read_uint32(ADDR_FLASH_PAGE + 255 * SIZE_uint32);



    	// uint16_t

		uint16_t val_1 = 0x4321;
		uint16_t val_2 = 0x89AB;
		uint16_t val_3 = 0x0102;
		uint16_t val_4 = 0x0435;

		HAL_UART_Transmit(&huart1, (uint8_t*)"\n\n\r!!!Erase page 31!!!\n\r", sizeof("\n\n\r!!!Erase page 31!!!\n\r"), 100);
		Flash_Erase_One_Page(ADDR_FLASH_PAGE); // очищення 31 сторінки

		HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Write!!!\n\r", sizeof("\n!!!Write!!!\n\r"), 100);
		// запис значень на початку і в кінці 31 сторінки
  		Flash_Write_uint16(ADDR_FLASH_PAGE + 0 * SIZE_uint32, val_1);
  		Flash_Write_uint16(ADDR_FLASH_PAGE + 1 * SIZE_uint32, val_2);
  		Flash_Write_uint16(ADDR_FLASH_PAGE + 3 * SIZE_uint32, val_3);
  		Flash_Write_uint16(ADDR_FLASH_PAGE + 255 * SIZE_uint32, val_4);

		HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Erase page 30!!!\n\r", sizeof("\n!!!Erase page 30!!!\n\r"), 100);
		Flash_Erase_One_Page(ADDR_FLASH_PAGE - SIZE_ONE_PAGE); // очищення 30 сторінки

		HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Write!!!\n\r", sizeof("\n!!!Write!!!\n\r"), 100);
		// запис значень на початку і в кінці 30 сторінки
  		Flash_Write_uint16(ADDR_FLASH_PAGE - SIZE_ONE_PAGE + 0x000, val_1);
  		Flash_Write_uint16(ADDR_FLASH_PAGE - SIZE_ONE_PAGE + 0x004, val_2);
  		Flash_Write_uint16(ADDR_FLASH_PAGE - SIZE_ONE_PAGE + 0x00C, val_3);
  		Flash_Write_uint16(ADDR_FLASH_PAGE - SIZE_ONE_PAGE + 0x3FC, val_4);

		HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Read!!!\n\r", sizeof("\n!!!Read!!!\n\r"), 100);
		// читання значень з 30 сторінки Flash-пам'яті
  		uint16_t a2 = Flash_Read_uint16(ADDR_FLASH_PAGE + 0 * SIZE_uint32);
  		uint16_t b2 = Flash_Read_uint16(ADDR_FLASH_PAGE + 1 * SIZE_uint32);
  		uint16_t c2 = Flash_Read_uint16(ADDR_FLASH_PAGE + 3 * SIZE_uint32);
  		uint16_t d2 = Flash_Read_uint16(ADDR_FLASH_PAGE + 255 * SIZE_uint32);


		uint8_t arr[] = "Lorem ipsum dolor sit amet";
		Flash_Write_Byte_Array(arr, 56);
		Flash_Read_By_Byte(ADDR_FLASH_PAGE, 56);


  /* USER CODE END 2 */

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
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2
   *
   */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void Flash_Erase_One_Page(uint32_t MYADDR)
{
	FLASH_EraseInitTypeDef EraseInitStruct; // структура для очищення флеша

	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES; // очищення сторінками, FLASH_TYPEERASE_MASSERASE - очищення всього флеша
	EraseInitStruct.PageAddress = MYADDR; // адреса сторінки;
	EraseInitStruct.NbPages = 1;          // кількість сторінок для очищення
	//EraseInitStruct.Banks = FLASH_BANK_1; // для більш потужник МК ніж STM32F103

	uint32_t page_error = 0; // змінна в яку запишеться адреса сторінки, при невдалому очищенні

	char str[64] = { 0, };

	//////// ОЧИЩЕННЯ Flash-пам'яті ////////
	HAL_FLASH_Unlock(); // розблокування Flash-пам'яті

	if (HAL_FLASHEx_Erase(&EraseInitStruct, &page_error) != HAL_OK)
	{
		// сталась помилка при очищенні сторінки
		uint32_t er = HAL_FLASH_GetError();
		snprintf(str, 64, "Error Flash_Erase(): %lu\n\r", er);
		HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
		while (1)
		{
		}
	}

	// очищення сторінки виконане успішно
	snprintf(str, 64, "Erase Flash from address 0x%08lX to address 0x%08lX OK\n\r", MYADDR, MYADDR+0x400-1);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);

	HAL_FLASH_Lock(); // заблокування Flash-пам'яті
}

void Flash_Write_uint32(uint32_t MYADDR, uint32_t val)
{
	char str[64] = { 0, };

	///////////// ЗАПИС у Flash-пам'ять ///////////////
	HAL_FLASH_Unlock(); // розблокування Flash-пам'яті

	if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, MYADDR, val) != HAL_OK)
	{
		uint32_t er = HAL_FLASH_GetError();
		snprintf(str, 64, "Error Flash_Write(): %lu\n\r", er);
		HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
		while (1)
		{
		}
	}

	snprintf(str, 64, "Write 32 bits (Hex: 0x%08lX) to address 0x%08lX OK\n\r", val, MYADDR);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);

	HAL_FLASH_Lock(); // заблокування Flash-пам'яті
}

uint32_t Flash_Read_uint32(uint32_t MYADDR)
{
	char str[64] = { 0, };

	/////////////// ЧИТАЄМО Flash-пам'ять ///////////////////
	uint32_t dig32 = *(uint32_t*) MYADDR; // читання числа за його адресою

	snprintf(str, 64, "Read 32 bits (Dec: %lu \tHex: 0x%08lX)", dig32, dig32);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
	snprintf(str, 64, " from address 0x%08lX \n\r", MYADDR);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);

	return dig32;
}

void Flash_Write_uint16(uint32_t MYADDR, uint16_t val)
{
	char str[64] = { 0, };

	///////////// ЗАПИС у Flash-пам'ять ///////////////
	HAL_FLASH_Unlock(); // розблокування Flash-пам'яті

	if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, MYADDR, val) != HAL_OK)
	{
		uint32_t er = HAL_FLASH_GetError();
		snprintf(str, 64, "Error Flash_Write(): %lu\n\r", er);
		HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
		while (1)
		{
		}
	}

	snprintf(str, 64, "Write 16 bits (Hex: 0x%08lX) to address 0x%08lX OK\n\r", val, MYADDR);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);

	HAL_FLASH_Lock(); // заблокування Flash-пам'яті
}

uint16_t Flash_Read_uint16(uint32_t MYADDR)
{
	char str[64] = { 0, };

	/////////////// ЧИТАЄМО Flash-пам'ять ///////////////////
	uint16_t dig16 = *(uint16_t*) MYADDR; // читання числа за його адресою

	snprintf(str, 64, "Read 16 bits (Dec: %lu \tHex: 0x%08lX)", dig16, dig16);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
	snprintf(str, 64, " from address 0x%08lX \n\r", MYADDR);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);

	return dig16;
}

void Flash_Write_uint64(uint32_t MYADDR, uint64_t val)
{
	char str[64] = { 0, };

	///////////// ЗАПИС у Flash-пам'ять ///////////////
	HAL_FLASH_Unlock(); // розблокування Flash-пам'яті

	if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, MYADDR, val) != HAL_OK)
	{
		uint32_t er = HAL_FLASH_GetError();
		snprintf(str, 64, "Error Flash_Write(): %lu\n\r", er);
		HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
		while (1)
		{
		}
	}

	snprintf(str, 64, "Write 64 bits (Hex: 0x%08lX) to address 0x%08lX OK\n\r", val, MYADDR);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);

	HAL_FLASH_Lock(); // заблокування Flash-пам'яті
}


uint64_t Flash_Read_uint64(uint32_t MYADDR)
{
	char str[64] = { 0, };

	/////////////// ЧИТАЄМО Flash-пам'ять ///////////////////
	uint64_t dig64 = *(uint64_t*) MYADDR; // читання числа за його адресою

	snprintf(str, 64, "Read 64 bits (Dec: %lu \tHex: 0x%08lX)", dig64, dig64);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
	snprintf(str, 64, " from address 0x%08lX \n\r", MYADDR);
	HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);

	return dig64;
}


void Flash_Write_Byte_Array(uint8_t phraze[], int byteCount)
{
	size_t SIZE_uint32 = sizeof(uint32_t);
	uint32_t SIZE_ONE_PAGE = 0x400;
	uint32_t ADDR_FLASH_PAGE = 0x08000000 + 31 * SIZE_ONE_PAGE;

	HAL_UART_Transmit(&huart1, (uint8_t*)"\n\n\r!!!Erase page 31!!!\n\r", sizeof("\n\n\r!!!Erase page 31!!!\n\r"), 100);
	Flash_Erase_One_Page(ADDR_FLASH_PAGE);

	HAL_UART_Transmit(&huart1, (uint8_t*)"\n!!!Write!!!\n\r", sizeof("\n!!!Write!!!\n\r"), 100);

	for(int i = 0; i < byteCount; i++)
	{
		char str[64] = { 0, };
		uint32_t currentAddress = ADDR_FLASH_PAGE + i * SIZE_uint32;
		HAL_FLASH_Unlock();

		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, currentAddress, phraze[i]) != HAL_OK)
		{
			uint32_t er = HAL_FLASH_GetError();
			snprintf(str, 64, "Error Flash_Write(): %lu\n\r", er);
			HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
			while (1) {}
		}

		snprintf(str, 64, "Write char (Hex: 0x%08lX) to address 0x%08lX OK\n\r",  phraze[i], currentAddress);
		HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);

		HAL_FLASH_Lock();
	}
}

void Flash_Read_By_Byte(uint32_t address, int byteCount)
{
	size_t SIZE_uint32 = sizeof(uint32_t);
	char str[64] = { 0, };

	for(int i = 0; i < byteCount; i++)
	{
		uint32_t currentAddress = address + i * SIZE_uint32;
		uint16_t value = *(uint16_t*) currentAddress;

		sprintf(str, "%c", value);
		HAL_UART_Transmit(&huart1, (uint8_t*) str, strlen(str), 100);
	}

}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
