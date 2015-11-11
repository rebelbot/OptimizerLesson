/**
  ******************************************************************************
  * @file    main.h 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    16-September-2015
  * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l4xx_it.h"

/* Discovery includes component */
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_glass_lcd.h"
#include "stm32l476g_discovery_idd.h"
#include "stm32l476g_discovery_gyroscope.h"
   
/* CMSIS OS includes component */
#include "cmsis_os.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  ULP_STOP2    = 0x00,
  ULP_STANDBY  = 0x01,
  ULP_OFF      = 0x02
} ULPMode;

typedef enum
{
  HWINIT_ERROR    = 0x00,
  HWINIT_STARTUP  = 0x01,
  HWINIT_IDD      = 0x02,
  HWINIT_STOP2    = 0x03,
  HWINIT_STANDBY  = 0x04
} HwInitMode;

typedef enum
{
  BACKUP_IDD        = 0x00,  /* IDD application backup data     */
  BACKUP_COMPASS    = 0x01,  /* Compass application backup data */
  BACKUP_SETTINGS   = 0x02   /* Kernel settings backup data     */
} DemoBackupId;

typedef struct
{
  uint32_t mode;  
} IddBackupData_TypeDef;

typedef struct
{
  uint32_t calibration;
  int32_t  xmax;
  int32_t  xmin;
  int32_t  ymax;
  int32_t  ymin;
  int32_t  zmax;
  int32_t  zmin;
} CompassBackupData_TypeDef;

typedef struct
{
  uint32_t lpmode;
} SettingsBackupData_TypeDef;

typedef struct
{
  /* IDD application */
  IddBackupData_TypeDef      idd;

  /* Global settings */
  SettingsBackupData_TypeDef settings;
} DemoBackupData_TypeDef;


/* Exported variables --------------------------------------------------------*/
extern void              (*EnterLowPowerMode)(void);
extern void              (*ExitLowPowerMode)(void);


/* Exported constants --------------------------------------------------------*/
#define DEMOBACKUP_AREA_ADDRESS 0x08080000   /* Backup data in first section of Bank2 */

#ifdef LAB3
#define AVERAGE_WINDOW_SIZE 100

#elif (defined LAB4) 
#define AVERAGE_WINDOW_SIZE 32 //128
#elif (defined LAB5)
#define AVERAGE_WINDOW_SIZE 32
#define AVERAGE_WINDOW_SHIFT_DIVISOR 5
#endif

#define square(val) (int32_t)((val) * (val))


/* Exported macros -----------------------------------------------------------*/
#define OsDelayMs(timeMS) (vTaskDelay((timeMS)/portTICK_PERIOD_MS))
/* Exported functions ------------------------------------------------------- */
void      SystemClock_Config(void);
void      SystemClock_BatterySupply_ClockIncrease(void);
void      SystemHardwareInit(HwInitMode Mode);
uint8_t   SystemStartupStatus(void);
void      Convert_IntegerIntoChar(uint32_t number, uint16_t *p_tab);
void      Error_Handler(const char * string);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
