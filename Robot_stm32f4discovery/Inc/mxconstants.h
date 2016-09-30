/**
  ******************************************************************************
  * File Name          : mxconstants.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MXCONSTANT_H
#define __MXCONSTANT_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define CS_I2C_SPI_Pin GPIO_PIN_3
#define CS_I2C_SPI_GPIO_Port GPIOE
#define ID_0_demux_0_Pin GPIO_PIN_4
#define ID_0_demux_0_GPIO_Port GPIOE
#define ID_1_demux_1_Pin GPIO_PIN_5
#define ID_1_demux_1_GPIO_Port GPIOE
#define ID_2_demux_2_Pin GPIO_PIN_6
#define ID_2_demux_2_GPIO_Port GPIOE
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define OTG_FS_PowerSwitchOn_Pin GPIO_PIN_0
#define OTG_FS_PowerSwitchOn_GPIO_Port GPIOC
#define NRF_MISO_Pin GPIO_PIN_2
#define NRF_MISO_GPIO_Port GPIOC
#define PDM_OUT_Pin GPIO_PIN_3
#define PDM_OUT_GPIO_Port GPIOC
#define MOTOR1_PWM_Pin GPIO_PIN_0
#define MOTOR1_PWM_GPIO_Port GPIOA
#define MOTOR2_ENCB_Pin GPIO_PIN_1
#define MOTOR2_ENCB_GPIO_Port GPIOA
#define MOTOR3_PWM_Pin GPIO_PIN_2
#define MOTOR3_PWM_GPIO_Port GPIOA
#define MOTOR4_PWM_Pin GPIO_PIN_3
#define MOTOR4_PWM_GPIO_Port GPIOA
#define MOTOR2_ENCA_Pin GPIO_PIN_5
#define MOTOR2_ENCA_GPIO_Port GPIOA
#define MOTOR3_ENCA_Pin GPIO_PIN_6
#define MOTOR3_ENCA_GPIO_Port GPIOA
#define MOTOR3_ENCB_Pin GPIO_PIN_7
#define MOTOR3_ENCB_GPIO_Port GPIOA
#define POSITION_SENSOR1_Pin GPIO_PIN_4
#define POSITION_SENSOR1_GPIO_Port GPIOC
#define POSITION_SENSOR2_Pin GPIO_PIN_5
#define POSITION_SENSOR2_GPIO_Port GPIOC
#define MOTOR3_DIR_Pin GPIO_PIN_0
#define MOTOR3_DIR_GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define IMU_IRQ_Pin GPIO_PIN_8
#define IMU_IRQ_GPIO_Port GPIOE
#define MOTOR1_ENCA_Pin GPIO_PIN_9
#define MOTOR1_ENCA_GPIO_Port GPIOE
#define MOTOR1_ENCB_Pin GPIO_PIN_11
#define MOTOR1_ENCB_GPIO_Port GPIOE
#define MOTOR1_DIR_Pin GPIO_PIN_13
#define MOTOR1_DIR_GPIO_Port GPIOE
#define MOTOR2_DIR_Pin GPIO_PIN_15
#define MOTOR2_DIR_GPIO_Port GPIOE
#define NRF_CS_Pin GPIO_PIN_12
#define NRF_CS_GPIO_Port GPIOB
#define NRF_SCK_Pin GPIO_PIN_13
#define NRF_SCK_GPIO_Port GPIOB
#define DRIBBLER_PWM_Pin GPIO_PIN_14
#define DRIBBLER_PWM_GPIO_Port GPIOB
#define NRF_MOSI_Pin GPIO_PIN_15
#define NRF_MOSI_GPIO_Port GPIOB
#define BANK_FULL_Pin GPIO_PIN_8
#define BANK_FULL_GPIO_Port GPIOD
#define CHARGE_BANK_Pin GPIO_PIN_9
#define CHARGE_BANK_GPIO_Port GPIOD
#define KICK_Pin GPIO_PIN_10
#define KICK_GPIO_Port GPIOD
#define KICKER_SELECT_Pin GPIO_PIN_11
#define KICKER_SELECT_GPIO_Port GPIOD
#define LD4_GPIO5_Pin GPIO_PIN_12
#define LD4_GPIO5_GPIO_Port GPIOD
#define LD3_GPIO4_Pin GPIO_PIN_13
#define LD3_GPIO4_GPIO_Port GPIOD
#define LD5_GPIO3_Pin GPIO_PIN_14
#define LD5_GPIO3_GPIO_Port GPIOD
#define LD6_GPIO2_Pin GPIO_PIN_15
#define LD6_GPIO2_GPIO_Port GPIOD
#define GPIO1_Pin GPIO_PIN_6
#define GPIO1_GPIO_Port GPIOC
#define EN_POWER_Pin GPIO_PIN_7
#define EN_POWER_GPIO_Port GPIOC
#define MOTOR2_PWM_Pin GPIO_PIN_8
#define MOTOR2_PWM_GPIO_Port GPIOC
#define VBUS_FS_Pin GPIO_PIN_9
#define VBUS_FS_GPIO_Port GPIOA
#define OTG_FS_ID_Pin GPIO_PIN_10
#define OTG_FS_ID_GPIO_Port GPIOA
#define OTG_FS_DM_Pin GPIO_PIN_11
#define OTG_FS_DM_GPIO_Port GPIOA
#define OTG_FS_DP_Pin GPIO_PIN_12
#define OTG_FS_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define Audio_RST_Pin GPIO_PIN_4
#define Audio_RST_GPIO_Port GPIOD
#define OTG_FS_OverCurrent_Pin GPIO_PIN_5
#define OTG_FS_OverCurrent_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define MOTOR4_ENCA_Pin GPIO_PIN_6
#define MOTOR4_ENCA_GPIO_Port GPIOB
#define MOTOR4_ENCB_Pin GPIO_PIN_7
#define MOTOR4_ENCB_GPIO_Port GPIOB
#define MOTOR4_DIR_Pin GPIO_PIN_8
#define MOTOR4_DIR_GPIO_Port GPIOB
#define MEMS_INT2_Pin GPIO_PIN_1
#define MEMS_INT2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MXCONSTANT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
