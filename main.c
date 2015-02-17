#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include <app_cfg.h>
#include <bsp.h>
#include <os.h>
#include <blink.h>
#include <pinmap.h>

#define APP_TASK_START_STK_SIZE		256u
/*
static OS_TCB AppTaskStartTCB;
static CPU_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];

static void AppTaskStart(void *p_arg);
*/
static void InitGPIO();

int main(void){
	OS_ERR err;


	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	while(1){
		GPIOD->BSRRL = GPIO_Pin_12;
		GPIOD->ODR ^= GPIO_Pin_12;
	}

/*	BSP_IntDisAll();
	OSInit(&err);
	if(err != OS_ERR_NONE){
		GPIOD->BSRRL = GPIO_Pin_14;
	}

/*	CREATION DE TACHES : Format de declaration		*
 * 	OSTaskCreate((OS_TCB 		*),
				 (CPU_CHAR		*),
				 (OS_TASK_PTR	 ),
				 (void 			*),
				 (OS_PRIO		 ),
				 (CPU_STK 		*),
				 (CPU_STK_SIZE 	 ),
				 (CPU_STK_SIZE 	 ),
				 (OS_MSG_QTY  	 ),
				 (OS_TICK  		 ),
				 (void 			*),
				 (OS_OPT 		 ),
				 (OS_ERR 		*)	);
*/
/*	OSTaskCreate((OS_TCB 		*)&AppTaskStartTCB,
				 (CPU_CHAR		*)"First task",
				 (OS_TASK_PTR	 )AppTaskStart,
				 (void 			*)0,
				 (OS_PRIO		 )APP_CFG_TASK_START_PRIO,
				 (CPU_STK 		*)&AppTaskStartStk[0],
				 (CPU_STK_SIZE 	 )APP_TASK_START_STK_SIZE / 10,
				 (CPU_STK_SIZE 	 )APP_TASK_START_STK_SIZE,
				 (OS_MSG_QTY  	 )0,
				 (OS_TICK  		 )0,
				 (void 			*)0,
				 (OS_OPT 		 )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
				 (OS_ERR 		*)&err	);

	if(err != OS_ERR_NONE){
		GPIOD->BSRRL = GPIO_Pin_14;
	}
*/
	OSStart(&err);
/*
	if(err != OS_ERR_NONE){
		GPIOD->BSRRL = GPIO_Pin_14;
		return -1;
	}*/
	return 0;

}

static void InitGPIO(){
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

static void AppTaskStart(void *p_arg)	{
	OS_ERR err;

	BSP_Init();
	CPU_Init();
	BSP_Tick_Init();

	while(DEF_ON){
		GPIOD->ODR ^= GPIO_Pin_12;
		OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}
