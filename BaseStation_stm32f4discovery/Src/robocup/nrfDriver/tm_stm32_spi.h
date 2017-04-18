/**
 * @author  Tilen Majerle
 * @email   tilen@majerle.eu
 * @website http://stm32f4-discovery.com
 * @link    http://stm32f4-discovery.com/2015/07/hal-library-08-spi-for-stm32fxxx/
 * @version v1.0
 * @ide     Keil uVision
 * @license MIT
 * @brief   SPI library for STM32Fxxx
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
#ifndef TM_SPI_H
#define TM_SPI_H 100

/**
 * @addtogroup TM_STM32Fxxx_HAL_Libraries
 * @{
 */

/**
 * @defgroup TM_SPI
 * @brief    SPI library for STM32Fxxx - http://stm32f4-discovery.com/2015/07/hal-library-08-spi-for-stm32fxxx/
 * @{
 *
 * It supports all 6 SPIs in master with 3 Lines Full Duplex mode
 *
 * \par Default SPI settings
 *
 * All six SPIs work the same principle by default:
 *	- Master mode
 *	- 8 data bits
 *	- Clock polarity low, data sampled at first edge, SPI mode 0
 *	- Prescaler set to 32
 *	- Firstbit MSB
 *	- Software SS pin configure
 *	- Direction is full duplex 3 wires
 *	
 *	\par Pinout
 *
 \verbatim
 |PINS PACK 1            |PINS PACK 2            |PINS PACK 3           |PINS PACK 4
 SPIX    |MOSI   MISO    SCK     |MOSI   MISO    SCK     |MOSI   MISO    SCK    |MOSI   MISO    SCK
 |
 SPI1    |PA7    PA6     PA5     |PB5    PB4     PB3     |                      |
 SPI2    |PC3    PC2     PB10    |PB15   PB14    PB13    |PI3    PI2     PI0    |PB15   PB14    PI1
 SPI3    |PB5    PB4     PB3     |PC12   PC11    PC10    |                      |
 SPI4    |PE6    PE5     PE2     |PE14   PE13    PE12    |                      |
 SPI5    |PF9    PF8     PF7     |PF11   PH7     PH6     |                      |
 SPI6    |PG14   PG12    PG13    |
 \endverbatim
 *
 * In case these pins are not good for you, you can use
 * TM_SPI_PinsPack_Custom in function and callback function will be called,
 * where you can initialize your custom pinout for your SPI peripheral
 *	
 * Possible changes to each SPI. Set this defines in your defines.h file.
 *	
 * Change x with 1-6, to match your SPI
 *
 \code
 //Default prescaler
 #define TM_SPIx_PRESCALER   SPI_BAUDRATEPRESCALER_32
 //Specify datasize
 #define TM_SPIx_DATASIZE    SPI_DATASIZE_8BIT
 //Specify which bit is first
 #define TM_SPIx_FIRSTBIT    SPI_FIRSTBIT_MSB
 //Mode, master or slave
 #define TM_SPIx_MASTERSLAVE SPI_MODE_MASTER
 //Specify mode of operation, clock polarity and clock phase
 #define TM_SPIx_MODE        TM_SPI_Mode_0
 \endcode
 *
 * \par Changelog
 *
 \verbatim
 Version 1.0
 - First release
 \endverbatim
 *
 * \par Dependencies
 *
 \verbatim
 - STM32Fxxx HAL
 - defines.h
 - attributes.h
 - TM GPIO
 \endverbatim
 */

#include "stm32f4xx_hal.h"

/**
 * @brief  Check SPI busy status
 */
#define SPI_IS_BUSY(SPIx)                   (((SPIx)->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0)

/**
 * @brief  SPI wait till end
 */
#define SPI_WAIT_TX(SPIx)                   while ((SPIx->SR & SPI_FLAG_TXE) == 0 || (SPIx->SR & SPI_FLAG_BSY))
#define SPI_WAIT_RX(SPIx)                   while ((SPIx->SR & SPI_FLAG_RXNE) == 0 || (SPIx->SR & SPI_FLAG_BSY))

/**
 * @brief  Checks if SPI is enabled
 */
#define SPI_CHECK_ENABLED(SPIx)             if (!((SPIx)->CR1 & SPI_CR1_SPE)) {return;}

/**
 * @brief  Checks if SPI is enabled and returns value from function if not 
 */
#define SPI_CHECK_ENABLED_RESP(SPIx, val)   if (!((SPIx)->CR1 & SPI_CR1_SPE)) {return (val);}

/**
 * @brief  Sends single byte over SPI
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  data: 8-bit data size to send over SPI
 * @retval Received byte from slave device
 */
static __INLINE uint8_t TM_SPI_Send(SPI_TypeDef* SPIx, uint8_t data) {
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED_RESP(SPIx, 0);

	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT_TX(SPIx);

	/* Fill output buffer with data */
	SPIx->DR = data;

	/* Wait for transmission to complete */
	SPI_WAIT_RX(SPIx);

	/* Return data from buffer */
	return SPIx->DR;
}

#endif

