#include "tm_stm32_spi.h"
#define STM32F4xx

/* Defines for alternate functions */
#if defined(STM32F4xx)
#define GPIO_AFx_SPI1    GPIO_AF5_SPI1
#define GPIO_AFx_SPI2    0x05
#define GPIO_AFx_SPI3    0x06
#endif

/* Private functions */
static void TM_SPIx_Init(SPI_TypeDef* SPIx, TM_SPI_Mode_t SPI_Mode, uint16_t SPI_BaudRatePrescaler, uint16_t SPI_MasterSlave, uint16_t SPI_FirstBit);
void TM_SPI1_INT_InitPins();
void TM_SPI2_INT_InitPins();

void TM_SPI_Init(SPI_TypeDef* SPIx) {
	/* Init with default settings */
#ifdef SPI1
	if (SPIx == SPI1) {
		TM_SPIx_Init(SPI1, TM_SPI1_MODE, TM_SPI1_PRESCALER, TM_SPI1_MASTERSLAVE, TM_SPI1_FIRSTBIT);
	}
#endif
#ifdef SPI2
	if (SPIx == SPI2) {
		TM_SPIx_Init(SPI2, TM_SPI2_MODE, TM_SPI2_PRESCALER, TM_SPI2_MASTERSLAVE, TM_SPI2_FIRSTBIT);
	}
#endif
}

void TM_SPI_SendMulti(SPI_TypeDef* SPIx, uint8_t* dataOut, uint8_t* dataIn, uint32_t count) {
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	while (count--) {
		/* Wait busy */
		SPI_WAIT_TX(SPIx);
		
		/* Fill output buffer with data */
		*(__IO uint8_t *)&SPIx->DR = *dataOut++;
		
		/* Wait for SPI to end everything */
		SPI_WAIT_RX(SPIx);
		
		/* Read data register */
		*dataIn++ = *(__IO uint8_t *)&SPIx->DR;
	}
}

void TM_SPI_WriteMulti(SPI_TypeDef* SPIx, uint8_t* dataOut, uint32_t count) {
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	while (count--) {
		/* Wait busy */
		SPI_WAIT_TX(SPIx);
		
		/* Fill output buffer with data */
		*(__IO uint8_t *)&SPIx->DR = *dataOut++;
		
		/* Wait for SPI to end everything */
		SPI_WAIT_RX(SPIx);
		
		/* Read data register */
		(void)*(__IO uint16_t *)&SPIx->DR;
	}
}

void TM_SPI_ReadMulti(SPI_TypeDef* SPIx, uint8_t* dataIn, uint8_t dummy, uint32_t count) {
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	while (count--) {
		/* Wait busy */
		SPI_WAIT_TX(SPIx);
		
		/* Fill output buffer with data */
		*(__IO uint8_t *)&SPIx->DR = dummy;
		
		/* Wait for SPI to end everything */
		SPI_WAIT_RX(SPIx);
		
		/* Save data to buffer */
		*dataIn++ = *(__IO uint8_t *)&SPIx->DR;
	}
}

/* Private functions */
SPI_HandleTypeDef SPIHandle;
static void TM_SPIx_Init(SPI_TypeDef* SPIx, TM_SPI_Mode_t SPI_Mode, uint16_t SPI_BaudRatePrescaler, uint16_t SPI_MasterSlave, uint16_t SPI_FirstBit) {
	
	/* Save instance */
	SPIHandle.Instance = SPIx;
	
#ifdef SPI1	
	if (SPIx == SPI1) {
		/* Enable SPI clock */
		__HAL_RCC_SPI1_CLK_ENABLE();
		
		/* Init pins */
		TM_SPI1_INT_InitPins();
		
		/* Set options */
		SPIHandle.Init.DataSize = TM_SPI1_DATASIZE;
	}
#endif
#ifdef SPI2
	if (SPIx == SPI2) {
		/* Enable SPI clock */
		//__HAL_RCC_SPI2_CLK_ENABLE();
		
		/* Init pins */
		//TM_SPI2_INT_InitPins();
		
		/* Set options */
		SPIHandle.Init.DataSize = TM_SPI2_DATASIZE;
	}
#endif

	/* Fill SPI settings */
	SPIHandle.Init.BaudRatePrescaler = SPI_BaudRatePrescaler;
	SPIHandle.Init.FirstBit = SPI_FirstBit;
	SPIHandle.Init.Mode = SPI_MasterSlave;
	
	SPIHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPIHandle.Init.CRCPolynomial = 7;
	SPIHandle.Init.TIMode = SPI_TIMODE_DISABLE;
	SPIHandle.Init.NSS = SPI_NSS_SOFT;
	SPIHandle.Init.Direction = SPI_DIRECTION_2LINES;
	
	/* SPI mode */
	if (SPI_Mode == TM_SPI_Mode_0) {
		SPIHandle.Init.CLKPolarity = SPI_POLARITY_LOW;
		SPIHandle.Init.CLKPhase = SPI_PHASE_1EDGE;
	} else if (SPI_Mode == TM_SPI_Mode_1) {
		SPIHandle.Init.CLKPolarity = SPI_POLARITY_LOW;
		SPIHandle.Init.CLKPhase = SPI_PHASE_2EDGE;
	} else if (SPI_Mode == TM_SPI_Mode_2) {
		SPIHandle.Init.CLKPolarity = SPI_POLARITY_HIGH;
		SPIHandle.Init.CLKPhase = SPI_PHASE_1EDGE;
	} else if (SPI_Mode == TM_SPI_Mode_3) {
		SPIHandle.Init.CLKPolarity = SPI_POLARITY_HIGH;
		SPIHandle.Init.CLKPhase = SPI_PHASE_2EDGE;
	}
	
	/* Disable first */
	__HAL_SPI_DISABLE(&SPIHandle);

	/* Init SPI */
	HAL_SPI_Init(&SPIHandle);

	/* Enable SPI */
	__HAL_SPI_ENABLE(&SPIHandle);
}

/* Private functions */
#ifdef SPI1
void TM_SPI1_INT_InitPins() {
	/* Init SPI pins */
	TM_GPIO_InitAlternate(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High, GPIO_AFx_SPI1);
}
#endif

#ifdef SPI2
void TM_SPI2_INT_InitPins() {
	/* Init SPI pins */
	TM_GPIO_InitAlternate(GPIOB, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High, GPIO_AFx_SPI2);
	TM_GPIO_InitAlternate(GPIOC, GPIO_PIN_2, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High, GPIO_AFx_SPI2);
}
#endif

