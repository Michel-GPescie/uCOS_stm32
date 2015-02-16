
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"


// Advantech USB-4750 Inputs (configured as Outputs on STM32 side)
// ---------------------------------------------------------------

// Slot A (IDI0 to IDI7) on PORTB

#define IDI_SLOT1_PORT	GPIOB

#define	IDI_0	GPIO_Pin_0
#define	IDI_1	GPIO_Pin_1
#define	IDI_2	GPIO_Pin_4
#define	IDI_3	GPIO_Pin_5

#define	IDI_4	GPIO_Pin_12
#define	IDI_5	GPIO_Pin_13
#define	IDI_6	GPIO_Pin_14
#define	IDI_7	GPIO_Pin_15

// Slot B (IDI8 to IDI15) on PORT C

#define IDI_SLOT2_PORT	GPIOC

#define	IDI_8	GPIO_Pin_1
#define	IDI_9	GPIO_Pin_2
#define	IDI_10	GPIO_Pin_4
#define	IDI_11	GPIO_Pin_5
#define	IDI_12	GPIO_Pin_6
#define	IDI_13	GPIO_Pin_8
#define	IDI_14	GPIO_Pin_9
#define	IDI_15	GPIO_Pin_11

// Advantech USB-4750 Outputs (configured as Inputs for STM32 side)
// ---------------------------------------------------------------

// Slot C (IDO0 to IDO7) on PORT D

#define IDO_SLOT1_PORT	GPIOD

#define	IDO_0	GPIO_Pin_8
#define	IDO_1	GPIO_Pin_9
#define	IDO_2	GPIO_Pin_10
#define	IDO_3	GPIO_Pin_11
#define	IDO_4	GPIO_Pin_12
#define	IDO_5	GPIO_Pin_13
#define	IDO_6	GPIO_Pin_14
#define	IDO_7	GPIO_Pin_15

// Slot C (IDO8 to IDO15) on PORT E

#define IDO_SLOT2_PORT	GPIOE

#define	IDO_8	GPIO_Pin_8
#define	IDO_9	GPIO_Pin_9
#define	IDO_10	GPIO_Pin_10
#define	IDO_11	GPIO_Pin_11
#define	IDO_12	GPIO_Pin_12
#define	IDO_13	GPIO_Pin_13
#define	IDO_14	GPIO_Pin_14
#define	IDO_15	GPIO_Pin_15
