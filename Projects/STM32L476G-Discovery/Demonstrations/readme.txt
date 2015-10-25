/**
  @page Demo MB1184
 
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    readme.txt 
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    21-July-2015
  * @brief   Description of MB1184 Demonstration
  ******************************************************************************
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
  @endverbatim

@par Demo Description

The STM32Cube Demonstration platform comes on top of the STM32CubeTM as a firmware
package that offers a full set of software components based on a modules architecture
allowing re-using them separately in standalone applications. All these modules are
managed by the STM32Cube Demonstration kernel allowing to dynamically adding new
modules and access to common resources (storage, graphical components and widgets,
memory management, Real-Time operating system)

The STM32Cube Demonstration platform is built around the FreeRTOS real time operating
system and uses almost the whole STM32 capability to offer a large scope of usage 
based on the STM32Cube HAL BSP and several middleware components.
 
A Binary file STM32CubeDemo_STM32L476G-Discovery-V1.0.2.hex is available in the 
"binary" directory. It can be downloaded using ST-Link Utility.
      
      
MENU NAVIGATION
========================================
Done with joystick keys:
- RIGHT & SEL:   launch application or enter in sub-menu 
                (SEL key is also used for Pause/Resume in Audio Playback application)
- LEFT:          exit application or back to upper menu level
- DOWN:          next menu item or down volume control in audio application
- UP:            previous menu item or volume up control in audio application 

LEDs
========================================
- LD5 is toggling during Audio record & playback applications else it remains OFF
- LD4 is set ON upon error detection

LOW POWER SCENARII
========================================
By default MCU goes into STOP2 mode after a period of inactivity:
- 10 seconds when running from USB ST-LINK
- 4 seconds when running from BATTERY (CR2032)
Use OPTION->LPMODE sub-menu to select alternative low power strategy:
- OFF (MCU keeps on running (only applicable when not running from battery))
Change in low power strategy applies upon selection and is saved in Backup area for 
next firmware demonstration start up or reset. 
Wake up is done upon any joystick key selection.

========================================
APPLICATIONS LIST
========================================
==========================
POWER UP from USB ST-LINK
==========================

 + IDD   (COMPATIBILITY WITH MFXSTM32L152 FW V2.6)
 --------------------------------------------------
 IDD measurement of the following modes:
  - RUN   (24Mhz from MSI range 9 in voltage range 2, No PLL, no RTC, no LSE, Flash ART on)
  - SLEEP (24Mhz from MSI range 9 in voltage range 2, No PLL, no RTC, no LSE, Flash ART on)
  - LPRUN  (LP run: 2MHz in voltage range 2 with low power regulator, no RTC, no LSE, Flash ART on)
  - PL SLP (LP sleep: 2MHz in voltage range 2 with low power regulator, no RTC, no LSE, Flash ART on)
  - STOP2  (no RTC, no LSE, Flash ART off)  
  - STDBY  (Standby: no RTC, no LSE, Flash ART off)  
  - SHTDWN (shutdown: no RTC, no LSE, Flash ART off)  

 + RECORD
 --------------
 Audio record 16-bit at 48Khz. Recorded file stored in QuadSPI flash.

 + PLAYER
 --------------
 Audio playback of WAV format file from either:
 - internal FLASH (audio.bin provided under "Utilities/Media/Audio" is to be flashed 
   at @ 0x08020000 with ST-Link Utility V3.5.x)
 - recorded audio file from QuadSPI FLASH
 
 + COMPASS
 --------------
 Compass application using the ST Mems LSM303C mounted on the MB1184 board.
 A calibration phase is require at first run, please perform rotations in the 
 3 axis, then press LEFT/RIGHT/SEL key to stop the calibration.
 Calibration data are saved in backup area.

 + SOUND
 --------------
 Soundmeter application with Audio record 16-bit at 48Khz

 + GUITAR
 --------------
 Acoustic guitar tuner application from the thickest to the thinnest string, 
 respectively :
    “STR1”             String 1 (E or 6E or Mi grave (French))
    “STR2”             String 2 (A or 5A or La (French))
    “STR3”             String 3 (D or 4D or Ré (French))
    “STR4”             String 4 (G or 3G or Sol (French))
    “STR5”             String 5 (B or 2B or Si (French))
    “STR6”             String 6 (e or 1E or Mi aigu (French))
 Output:
    “    “ when recording sample is invalid (board needs to be closed enough to the guitar)
    “ OK “ when string is in tune
    “ ++ “ when string needs to be tightened
    “  + ” when string needs to be tightened but close to in tune
    “ -- “ when string is too tightened
    “  - ” when string is too tightened but close to in tune

 + VDD MCU
 --------------
  VDD MCU from VREFINT (ADC)


==========================
POWER UP from VBAT (CR2032)
==========================
Remove Jumper JP3 (RST) and 2 Jumpers on CN3 for ST -Link
Put Jumper JP6 in BATT position

 + IDD   (COMPATIBILITY WITH MFXSTM32L152 FW V2.6)
 --------------------------------------------------
 IDD measurement of the following modes:
  - RUN    (Run: 24MHz in voltage range 2, No PLL, no RTC, no LSE, Flash ART on)
  - SLEEP  (Sleep: 24MHz in voltage range 2, No PLL, no RTC, no LSE, Flash ART on)
  - LPRUN  (LP run: 2MHz in voltage range 2 with low power regulator, no RTC, no LSE, Flash ART on)
  - PL SLP (LP sleep: 2MHz in voltage range 2 with low power regulator, no RTC, no LSE, Flash ART on)
  - STOP2  (no RTC, no LSE, Flash ART off)  
  - STDBY  (Standby: no RTC, no LSE, Flash ART off)  
  - SHTDWN (shutdown: no RTC, no LSE, Flash ART off)  

 + VDD MCU
 --------------
  VDD MCU from VREFINT (ADC)

 + COMPASS
 --------------
 Compass application using the ST Mems LSM303C mounted on the MB1184 board.
 A calibration phase is require at first run, please perform rotations in the 
 3 axis, then press LEFT/RIGHT/SEL key to stop the calibration.
 Calibration data are saved in backup area.

 + SOUDMETER
 --------------
  Soundmeter application with Audio record 16-bit at 48Khz
  Runs at HCLK 16Mhz
  
  
@par Hardware and Software environment

  - This demonstration runs on STM32L476xx devices.
    
  - This example has been tested with STM32L476G-DISCO evaluation board (MB1184C) and can be
    easily tailored to any other supported device and development board. 
    
  - Binary file STM32CubeDemo_STM32L476G-Discovery-V1.0.2.hex in the "binary" directory can be downloaded using
  ST-Link Utility (v3.5.1)

  - Binary file generated with IAR Workbench V7.40 in High optimization mode 
   

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 
