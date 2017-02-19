#include "tm_stm32_gpio.h"

/* Private functions */
void TM_GPIO_INT_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,
		TM_GPIO_Mode_t GPIO_Mode, TM_GPIO_OType_t GPIO_OType,
		TM_GPIO_PuPd_t GPIO_PuPd, TM_GPIO_Speed_t GPIO_Speed);

void TM_GPIO_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,
		TM_GPIO_Mode_t GPIO_Mode, TM_GPIO_OType_t GPIO_OType,
		TM_GPIO_PuPd_t GPIO_PuPd, TM_GPIO_Speed_t GPIO_Speed) {
	/* Check input */
	if (GPIO_Pin == 0x00) {
		return;
	}

	/* Enable clock for GPIO */

	RCC->AHB1ENR |= (1
			<< (((uint32_t) GPIOx - (GPIOA_BASE))
					/ ((GPIOB_BASE) - (GPIOA_BASE))));

	/* Do initialization */
	TM_GPIO_INT_Init(GPIOx, GPIO_Pin, GPIO_Mode, GPIO_OType, GPIO_PuPd,
			GPIO_Speed);
}

void TM_GPIO_InitAlternate(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,
		TM_GPIO_OType_t GPIO_OType, TM_GPIO_PuPd_t GPIO_PuPd,
		TM_GPIO_Speed_t GPIO_Speed, uint8_t Alternate) {
	uint32_t pinpos;

	/* Enable GPIOx clock */
	RCC->AHB1ENR |= (1
			<< (((uint32_t) GPIOx - (GPIOA_BASE))
					/ ((GPIOB_BASE) - (GPIOA_BASE))));

	/* Set alternate functions for all pins */
	for (pinpos = 0; pinpos < 0x10; pinpos++) {
		/* Check pin */
		if ((GPIO_Pin & (1 << pinpos)) == 0) {
			continue;
		}

		/* Set alternate function */
		GPIOx->AFR[pinpos >> 0x03] = (GPIOx->AFR[pinpos >> 0x03]
				& ~(0x0F << (4 * (pinpos & 0x07))))
				| (Alternate << (4 * (pinpos & 0x07)));
	}

	/* Do initialization */
	TM_GPIO_INT_Init(GPIOx, GPIO_Pin, TM_GPIO_Mode_AF, GPIO_OType, GPIO_PuPd,
			GPIO_Speed);
}

/* Private functions */

void TM_GPIO_INT_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,
		TM_GPIO_Mode_t GPIO_Mode, TM_GPIO_OType_t GPIO_OType,
		TM_GPIO_PuPd_t GPIO_PuPd, TM_GPIO_Speed_t GPIO_Speed) {
	uint8_t pinpos;

	/* Go through all pins */
	for (pinpos = 0; pinpos < 0x10; pinpos++) {
		/* Check if pin available */
		if ((GPIO_Pin & (1 << pinpos)) == 0) {
			continue;
		}

		/* Set GPIO PUPD register */
		GPIOx->PUPDR = (GPIOx->PUPDR & ~(0x03 << (2 * pinpos)))
				| ((uint32_t) (GPIO_PuPd << (2 * pinpos)));

		/* Set GPIO MODE register */
		GPIOx->MODER = (GPIOx->MODER & ~((uint32_t) (0x03 << (2 * pinpos))))
				| ((uint32_t) (GPIO_Mode << (2 * pinpos)));

		/* Set only if output or alternate functions */
		if (GPIO_Mode == TM_GPIO_Mode_OUT || GPIO_Mode == TM_GPIO_Mode_AF) {
			/* Set GPIO OTYPE register */
			GPIOx->OTYPER = (GPIOx->OTYPER & ~(uint16_t) (0x01 << pinpos))
					| ((uint16_t) (GPIO_OType << pinpos));

			/* Set GPIO OSPEED register */
			GPIOx->OSPEEDR = (GPIOx->OSPEEDR
					& ~((uint32_t) (0x03 << (2 * pinpos))))
					| ((uint32_t) (GPIO_Speed << (2 * pinpos)));
		}
	}
}
