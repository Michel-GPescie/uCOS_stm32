#include <app_cfg.h>
#include <bsp.h>
#include <os.h>

static OS_TCB AppTaskStartTCB;
static CPU_STK AppTaskStart[APP_TASK_START_STK_SIZE];

static void AppTaskStart(void *p_arg);
static void InitGPIO();

void main(void){
	OS_ERR err;

	BSP_IntDisAll();
	OSInit(&err);
	if(err != OS_ERR_NONE){

	}
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
