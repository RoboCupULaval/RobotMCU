/** 
 * @author  Tilen Majerle
 * @email   tilen@majerle.eu
 * @website http://stm32f4-discovery.com
 * @link    http://stm32f4-discovery.com/2015/07/hal-library-1-5-gpio-library-for-stm32fxxx/
 * @version v1.0
 * @ide     Keil uVision
 * @license MIT
 * @brief   GPIO Library for STM32F4xx and STM32F7xx devices
 *
\verbatim
   ----------------------------------------------------------------------
    Copyright (c) 2016 Tilen Majerle

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge,
    publish, distribute, sublicense, and/or sell copies of the Software, 
    and to permit persons to whom the Software is furnished to do so, 
    subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
    AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
   ----------------------------------------------------------------------
\endverbatim
 */
#ifndef TM_GPIO_H
#define TM_GPIO_H 100

	
/**
 * @addtogroup TM_STM32Fxxx_HAL_Libraries
 * @{
 */

/**
 * @defgroup TM_GPIO
 * @brief    TM GPIO Library for STM32Fxxx
 * @{
 *
 * GPIO library can be used for GPIO pins. 
 *
 * It features fast initialization methods as well pin input/output methods.
 *
 * It can be used as replacement for STD/HAL drivers GPIO library.
 *
 * \par Changelog
 *
\verbatim
 Version 1.0
  - Initial release
\endverbatim
 *
 * \par Dependencies
 *
\verbatim
 - STM32Fxxx HAL
 - defines.h
\endverbatim
 */
#include "../../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"

/**
 * @brief GPIO Pins declarations 
 * @note  For STD Periph drivers compatibility
 */

#ifndef GPIO_Pin_0
#define GPIO_Pin_0		((uint16_t)0x0001)
#define GPIO_Pin_1		((uint16_t)0x0002)
#define GPIO_Pin_2		((uint16_t)0x0004)
#define GPIO_Pin_3		((uint16_t)0x0008)
#define GPIO_Pin_4		((uint16_t)0x0010)
#define GPIO_Pin_5		((uint16_t)0x0020)
#define GPIO_Pin_6		((uint16_t)0x0040)
#define GPIO_Pin_7		((uint16_t)0x0080)
#define GPIO_Pin_8		((uint16_t)0x0100)
#define GPIO_Pin_9		((uint16_t)0x0200)
#define GPIO_Pin_10		((uint16_t)0x0400)
#define GPIO_Pin_11		((uint16_t)0x0800)
#define GPIO_Pin_12		((uint16_t)0x1000)
#define GPIO_Pin_13		((uint16_t)0x2000)
#define GPIO_Pin_14		((uint16_t)0x4000)
#define GPIO_Pin_15		((uint16_t)0x8000)
#define GPIO_Pin_All	((uint16_t)0xFFFF)
#endif

/**
 * @}
 */

/**
 * @defgroup TM_GPIO_Typedefs
 * @brief    GPIO Typedefs used for GPIO library for initialization purposes
 * @{
 */

/**
 * @brief GPIO Mode enumeration
 */
typedef enum {
	TM_GPIO_Mode_IN = 0x00,  /*!< GPIO Pin as General Purpose Input */
	TM_GPIO_Mode_OUT = 0x01, /*!< GPIO Pin as General Purpose Output */
	TM_GPIO_Mode_AF = 0x02,  /*!< GPIO Pin as Alternate Function */
	TM_GPIO_Mode_AN = 0x03,  /*!< GPIO Pin as Analog input/output */
} TM_GPIO_Mode_t;

/**
 * @brief GPIO Output type enumeration
 */
typedef enum {
	TM_GPIO_OType_PP = 0x00, /*!< GPIO Output Type Push-Pull */
	TM_GPIO_OType_OD = 0x01  /*!< GPIO Output Type Open-Drain */
} TM_GPIO_OType_t;

/**
 * @brief  GPIO Speed enumeration
 */
typedef enum {
	TM_GPIO_Speed_Low = 0x00,    /*!< GPIO Speed Low */
	TM_GPIO_Speed_Medium = 0x01, /*!< GPIO Speed Medium */
	TM_GPIO_Speed_Fast = 0x02,   /*!< GPIO Speed Fast, not available on STM32F0xx devices */
	TM_GPIO_Speed_High = 0x03    /*!< GPIO Speed High */
} TM_GPIO_Speed_t;

/**
 * @brief GPIO pull resistors enumeration
 */
typedef enum {
	TM_GPIO_PuPd_NOPULL = 0x00, /*!< No pull resistor */
	TM_GPIO_PuPd_UP = 0x01,     /*!< Pull up resistor enabled */
	TM_GPIO_PuPd_DOWN = 0x02    /*!< Pull down resistor enabled */
} TM_GPIO_PuPd_t;

/**
 * @} TM_GPIO_Typedefs
 */

/**
 * @defgroup TM_GPIO_Functions
 * @brief    GPIO Functions
 * @{
 */
 
/**
 * @brief  Initializes GPIO pins(s)
 * @note   This function also enables clock for GPIO port
 * @param  GPIOx: Pointer to GPIOx port you will use for initialization
 * @param  GPIO_Pin: GPIO pin(s) you will use for initialization
 * @param  GPIO_Mode: Select GPIO mode. This parameter can be a value of @ref TM_GPIO_Mode_t enumeration
 * @param  GPIO_OType: Select GPIO Output type. This parameter can be a value of @ref TM_GPIO_OType_t enumeration
 * @param  GPIO_PuPd: Select GPIO pull resistor. This parameter can be a value of @ref TM_GPIO_PuPd_t enumeration
 * @param  GPIO_Speed: Select GPIO speed. This parameter can be a value of @ref TM_GPIO_Speed_t enumeration
 * @retval None
 */
void TM_GPIO_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, TM_GPIO_Mode_t GPIO_Mode, TM_GPIO_OType_t GPIO_OType, TM_GPIO_PuPd_t GPIO_PuPd, TM_GPIO_Speed_t GPIO_Speed);

/**
 * @brief  Initializes GPIO pins(s) as alternate function
 * @note   This function also enables clock for GPIO port
 * @param  GPIOx: Pointer to GPIOx port you will use for initialization
 * @param  GPIO_Pin: GPIO pin(s) you will use for initialization
 * @param  GPIO_OType: Select GPIO Output type. This parameter can be a value of @ref TM_GPIO_OType_t enumeration
 * @param  GPIO_PuPd: Select GPIO pull resistor. This parameter can be a value of @ref TM_GPIO_PuPd_t enumeration
 * @param  GPIO_Speed: Select GPIO speed. This parameter can be a value of @ref TM_GPIO_Speed_t enumeration
 * @param  Alternate: Alternate function you will use
 * @retval None
 */
void TM_GPIO_InitAlternate(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, TM_GPIO_OType_t GPIO_OType, TM_GPIO_PuPd_t GPIO_PuPd, TM_GPIO_Speed_t GPIO_Speed, uint8_t Alternate);


/**
 * @brief  Sets pin(s) low
 * @note   Defined as macro to get maximum speed using register access
 * @param  GPIOx: GPIOx PORT where you want to set pin low
 * @param  GPIO_Pin: Select GPIO pin(s). You can select more pins with | (OR) operator to set them low
 * @retval None
 */
#define TM_GPIO_SetPinLow(GPIOx, GPIO_Pin)			((GPIOx)->BSRR = (uint32_t)(((uint32_t)GPIO_Pin) << 16))

/**
 * @brief  Sets pin(s) high
 * @note   Defined as macro to get maximum speed using register access
 * @param  GPIOx: GPIOx PORT where you want to set pin high
 * @param  GPIO_Pin: Select GPIO pin(s). You can select more pins with | (OR) operator to set them high
 * @retval None
 */
#define TM_GPIO_SetPinHigh(GPIOx, GPIO_Pin)			((GPIOx)->BSRR = (uint32_t)(GPIO_Pin))

#endif
