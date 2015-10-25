/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    16-September-2015
  * @brief   This file provides main program functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h" 
#include "stm32l4xx_hal_cortex.h"
#include "SlidingWindow.h"

/** @addtogroup CORE
  * @{
  */

/** @defgroup MAIN
* @brief main file
* @{
*/ 


/** @defgroup MAIN_Private_TypesDefinitions
* @{
*/ 
#ifdef LAB0

#elif LAB1
	
#elif (defined LAB3)	
//globally defined
SlidingWindow16 average_gyro;
int16_t windowbuffer[AVERAGE_WINDOW_SIZE];
#endif
	
#if (defined LAB2) | (defined LAB3)	| (defined LAB4) | (defined LAB5)
	#define LED5_PROFILE__START BSP_LED_On(LED5)
	#define LED5_PROFILE__STOP BSP_LED_Off(LED5)
#endif 



#if (defined LAB3)	| (defined LAB4) | (defined LAB5)

int32_t sq_rt(int32_t val)
{
	int32_t root = 0;
	
	if(val < 0)
		return root;
	while(root*root < val)
	{
		root++;
	}
	return root;
}
#define MAGNITUDE_3AXIS(x,y,z) (sq_rt(((int32_t)(square(x))) + (square(y)) + (square(z))))
/************ Use to see floating point library ******
 ////////takes up a lot of space ////////////////////
#elif (defined LAB3)

double CalcMagn(int16_t x, int16_t y, int16_t z )
{
    int doubX = square(x);
    int doubY = square(y);
		int doubZ = square(z);
    double magnitude = doubX +  doubY + doubZ;
    pow(magnitude, 0.5);
    return magnitude;
}

#define MAGNITUDE_3AXIS(x,y,z) (uint16_t)(CalcMagn((x) ,(y) ,(z)))
****************/
#endif

/**
* @}
*/ 

/** @defgroup MAIN_Private_Defines
* @{
*/
#define MIN_IDLE_TIME_BATTERY           4000    /* Time in ms to automatically enter low power in Battery mode */
#define MIN_IDLE_TIME_USB               10000   /* Time in ms to automatically enter low power in USB-powered mode */

osThreadId tid_thrLED;                  // Thread id of thread: LED
osThreadId tid_isrLED;                  // Thread id of thread: thrIsrLED 

/**
* @}
*/ 


/** @defgroup MAIN_Private_Macros
* @{
*/ 
/**
* @}
*/ 


/** @defgroup MAIN_Private_Variables
* @{
*/
static uint8_t StartupString[] = " REBELBOT";


/* HW resources initialization variables */
static FlagStatus JoyInitialized = RESET;
static FlagStatus LcdInitialized = RESET;
static FlagStatus LedInitialized = RESET;

/**
* @}
*/ 

/** @defgroup MAIN_Private_FunctionPrototypes
* @{
*/
static void thrMain(void const * argument);

/**
* @}
*/ 

/** @defgroup MAIN_Private_Functions
* @{
*/ 
/*
 * isrLED: toggle LED based on isr callback
 */
 #ifdef LAB5
#pragma push 
#pragma O3
#endif

void thrIsrLED(void const *argument) {
#if (defined LAB2) | (defined LAB3) | (defined LAB4) | (defined LAB5)
	uint8_t strbuff[20];
#endif
#ifdef LAB2	
		static int count =0;
#elif (defined LAB4) | (defined LAB5)
	//locally defined in task
	SlidingWindow16 average_gyro;
	int16_t windowbuffer[AVERAGE_WINDOW_SIZE];	
#endif

#if (defined LAB3)	| (defined LAB4) | (defined LAB5)

	SlidingWindow16Init(&average_gyro,AVERAGE_WINDOW_SIZE, windowbuffer );
	float GyroBuffer[3];
#endif	

	
  for (;;) {
    osSignalWait(0x0001, osWaitForever);
		
#if (defined LAB3)	| (defined LAB4) | (defined LAB5)
		
		//1. Get sample and calculate the magnitude
		BSP_GYRO_GetXYZ(GyroBuffer); 
		int16_t sample = MAGNITUDE_3AXIS(GyroBuffer[AXIS_DIR__X],GyroBuffer[AXIS_DIR__Y],GyroBuffer[AXIS_DIR__Z]);

		//2. Process sample
		SlidingWindowInsertSampleAndUpdateAverage16(&average_gyro, sample);
		int16_t ave = 0;
		
		SlidingWindowGetAverage16(&average_gyro, &ave);

		//3. Print Average result

		BSP_LCD_GLASS_Clear();
		
		/* Get the current menu */
		sprintf((char *)strbuff, "%d", ave);
		BSP_LCD_GLASS_DisplayString((uint8_t *)strbuff);
		
#elif LAB2		
		//Print result on screen
		/* Clear the LCD GLASS */
		BSP_LCD_GLASS_Clear();
		
		/* Get the current menu */
		sprintf((char *)strbuff, "%d", ++count);
		BSP_LCD_GLASS_DisplayString((uint8_t *)strbuff);
#endif

//Toggle LED for profiling		
#ifdef LAB1		
		/* Toggle LED5 */
		BSP_LED_Toggle(LED5);
#elif  (defined LAB2) | (defined LAB3) | (defined LAB4) | (defined LAB5)
    LED5_PROFILE__STOP;
#endif
  }

}
#ifdef LAB5
#pragma pop 
#endif

/*
 * thrLED: blink LED and check button state
 */
void thrLED(void const *argument) 
{
#if (defined LAB0) | (defined LAB1) | (defined LAB2)	
	int count= 0;
#endif

  for (;;) 
	{
    osSignalWait(0x0001, osWaitForever);
    /* Toggle LED4 */
    BSP_LED_Toggle(LED4);
#if (defined LAB0) | (defined LAB1)
		
		char string[8] = "";
		sprintf(string, "Lp %d", count++);
		BSP_LCD_GLASS_Clear();
		BSP_LCD_GLASS_DisplayString((uint8_t *)string);
#endif
	
  }

}


/**
* @brief  Main program
* @param  None
* @retval int
*/
int main(void)
{
  /* STM32L4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

    /* 80 MHz PLL ON */
    SystemClock_Config();
  
  /* Create Start task */
  osThreadDef(Main_Thread, thrMain, osPriorityNormal, 0, 2 * configMINIMAL_STACK_SIZE);
  osThreadCreate (osThread(Main_Thread), NULL);
	
	osThreadDef(LED_Thread, thrLED, osPriorityNormal, 1, 2 * configMINIMAL_STACK_SIZE);
	osThreadDef(ISR_LED_Thread, thrIsrLED, osPriorityNormal, 1, 1 * configMINIMAL_STACK_SIZE);
  
  tid_thrLED = osThreadCreate (osThread(LED_Thread), NULL);        // create LED thread
	tid_isrLED = osThreadCreate (osThread(ISR_LED_Thread), NULL);        // create LED thread


  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  for( ;; );

}

/**
  * @brief  Start task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */

static void thrMainInit(void)
{
  
  /* Configure minimum hardware resources at boot */
  SystemHardwareInit(HWINIT_STARTUP);

	/* Clear the reset flags */
  __HAL_RCC_CLEAR_RESET_FLAGS();
	/* Display the demonstration window */
	BSP_LCD_GLASS_ScrollSentence(StartupString, 1, SCROLL_SPEED_HIGH);
	/* Clear LCD Display */
	BSP_LCD_GLASS_Clear();

}
static void thrMain(void const * argument)
{

  thrMainInit();
  HAL_Delay(2000);

  while(1)
	{
		OsDelayMs(500);
		
		//signal other task
		osSignalSet(tid_thrLED, 0x0001);
	}

}



/**
  * @brief  System Clock Configuration on USB/ST-Link
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (MSI)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            MSI Frequency(Hz)              = 2000000
  *            PLL_M                          = 1
  *            PLL_N                          = 80
  *            PLL_R                          = 2
  *            PLL_P                          = 7
  *            PLL_Q                          = 4
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* oscillator and clocks configs */
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  
  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  if(HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler("SYSCLK");
  }

  /* Disable Power Control clock */
  __HAL_RCC_PWR_CLK_DISABLE();

  /* 80 Mhz from PLL with MSI 8Mhz as source clock */
  /* MSI is enabled after System reset, activate PLL with MSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_7;   /* 8 Mhz */
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler("PLL ERR");
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler("RCC ERR");
  }
}




/**
  * @brief  System Clock Speed increase when power is battery supplied
  *         Set MSI to range 8 (16 MHz) and turn on PLL to apply PLLM divider 2
  *         (system clock speed is increased from 2 to 16 MHz)  
  * @note  API is called before starting SoundMeter tests 
  * @note  API is called only when the device power is battery-supplied         
  * @param  None
  * @retval None
  */  
void SystemClock_BatterySupply_ClockIncrease(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  HAL_PWREx_DisableLowPowerRunMode();
  
  /* Disable Power Control clock once PWR register is updated */
  __HAL_RCC_PWR_CLK_DISABLE();  

  /* MSI is enabled in range 8 (16 Mhz) with PLLM divider 2 from PLL */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_8; /* to 16 MHz */
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler("RCC ERR");
  }
}




/**
  * @brief  System Power Configuration at Boot or from WakeUp
  * @param  Mode: Purpose of HW initialization 
  *               (HWINIT_STARTUP/HWINIT_IDD/HWINIT_STOP2/HWINIT_STANDBY)
  * @retval None
  */
void SystemHardwareInit(HwInitMode Mode)
{
  if(Mode == HWINIT_ERROR)
  {
    Error_Handler("HWINIT");
  }
  
  /* Initialize LED 3 and LED 4  */
  if(LedInitialized != SET)
  {
    BSP_LED_Init(LED4);
    BSP_LED_Init(LED5);
    LedInitialized = SET;
  }

  /* STOP2 Low power mode:  Need to keep LCD and joystick keys active */
  /*                        Else reactivate all consuming resources   */
  if(Mode != HWINIT_STOP2)
  {
    /* Initialize the joystick in interrupt mode */
    if(JoyInitialized != SET)
    {
      BSP_JOY_Init(JOY_MODE_EXTI); //EXTI0_IRQHandler_Config();
      JoyInitialized = SET;
    }
    
    /* Initialize the LCD */
    if(LcdInitialized != SET)
    {
      BSP_LCD_GLASS_Init();
      LcdInitialized = SET;
    }
    
    /* Return from IDD measurement */
    if(Mode == HWINIT_IDD)
    {
      GPIO_InitTypeDef GPIO_InitStruct;

      /*##-1- Configure the GPIOs for MFX ######################################*/
      /* Enable GPIO clock */
      DISCOVERY_I2C2_SDA_GPIO_CLK_ENABLE();
      DISCOVERY_I2C2_SCL_GPIO_CLK_ENABLE();

      /* Configure I2C Rx/Tx as alternate function  */
      GPIO_InitStruct.Pin       = DISCOVERY_I2C2_SCL_PIN | DISCOVERY_I2C2_SDA_PIN;
      GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
      GPIO_InitStruct.Pull      = GPIO_PULLUP;
      GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
      GPIO_InitStruct.Alternate = DISCOVERY_I2C2_SCL_SDA_AF;
      HAL_GPIO_Init(DISCOVERY_I2C2_SCL_GPIO_PORT, &GPIO_InitStruct);

      /*##-2- Configure the Discovery I2C2 peripheral for MFX ##################*/
      /* Enable Discovery_I2C2 clock */
      DISCOVERY_I2C2_CLK_ENABLE();

      /* Enable PWR clock */
      __HAL_RCC_PWR_CLK_ENABLE();
    }
		
		  /* Init Gyro Mems */
		if(BSP_GYRO_Init() != GYRO_OK)
		{
			/* Initialization Error */
			 Error_Handler("SENSOR"); 
		}
  }
  else
  {
    /* Enable PWR clock */
    __HAL_RCC_PWR_CLK_ENABLE();
    
    /* Enable I2C2 clock */
    __HAL_RCC_I2C2_CLK_ENABLE();

  }
}




/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  if (GPIO_Pin == SEL_JOY_PIN)
  {
		//Turn on LED to profile delay time in task
#if (defined LAB2) | (defined LAB3)	| (defined LAB4) | (defined LAB5)
		LED5_PROFILE__START;
#endif
		
    /* SEnd callback to thrIsrLED */		
		osSignalSet(tid_isrLED, 0x0001);
	}

}


/**
  * @brief converts a 32bit unsigned int into ASCII 
  * @caller several callers for display values
  * @param Number digit to displays
  *  p_tab values in array in ASCII   
  * @retval None
  */ 
void Convert_IntegerIntoChar(uint32_t number, uint16_t *p_tab)
{
  uint16_t units=0, tens=0, hundreds=0, thousands=0, tenthousand=0, hundredthousand=0;
  
  units = ((((number%100000)%10000)%1000)%100)%10;
  tens = (((((number-units)/10)%10000)%1000)%100)%10;
  hundreds = ((((number-tens-units)/100)%1000)%100)%10;
  thousands = (((number-hundreds-tens-units)/1000)%100)%10;
  tenthousand = ((number-thousands-hundreds-tens-units)/10000)%10;
  hundredthousand = ((number-tenthousand-thousands-hundreds-tens-units)/100000);
  
  *(p_tab+5) = units + 0x30;
  *(p_tab+4) = tens + 0x30;
  *(p_tab+3) = hundreds + 0x30;
  *(p_tab+2) = thousands + 0x30;
  *(p_tab+1) = tenthousand + 0x30;
  *(p_tab+0) = hundredthousand + 0x30;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(const char * string)
{
	if(LcdInitialized == SET)
	{	
		BSP_LCD_GLASS_Clear();
		BSP_LCD_GLASS_DisplayString((uint8_t *)string);
	}
  while(1);

}

/* FreeRTOS hooks */
/**
  * @brief  Application Idle Hook
  * @param  None 
  * @retval None
  */
void vApplicationIdleHook(void) 
{
}

/**
  * @brief  Application Malloc failure Hook
  * @param  None 
  * @retval None
  */
void vApplicationMallocFailedHook(void)
{
  Error_Handler("APP FAIL");
}

/**
  * @brief  vApplication Stack Overflow
  * @param  None 
  * @retval None
  */
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
  Error_Handler("OVRFLO");
}

#ifdef USE_FULL_ASSERT
/**
* @brief  assert_failed
*         Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  File: pointer to the source file name
* @param  Line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line
  number,ex: printf("Wrong parameters value: file %s on line %d\r\n", 
  file, line) */
  
  /* Infinite loop */
  while (1)
  {}
}
#endif


/**
* @}
*/ 

/**
* @}
*/ 

/**
* @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
