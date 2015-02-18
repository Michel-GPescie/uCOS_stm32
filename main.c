#include  <app_cfg.h>
#include  <includes.h>

#define BUTTON (GPIOA->IDR & 0x0001)
#define BUTTON_STK_SIZE 16u
#define BUTTON_TASK_PRIO 8u

/* Tasks' control blocks. ---------------------------------------------------------------*/

static  OS_TCB   AppTaskStartTCB;
static OS_TCB buttonTCB;

/* Tasks' stack. ------------------------------------------------------------------------*/

static  CPU_STK  AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];
static	CPU_STK buttonSTK[BUTTON_STK_SIZE];

/* Tasks. -------------------------------------------------------------------------------*/

static  void  AppTaskStart          (void     *p_arg);
static void buttonTask(void *p_arg);

/* Main program. ------------------------------------------------------------------------*/

int main(void) {

	OS_ERR  			oseError;

	GPIO_InitTypeDef	GPIO_InitStructure;

    /* GPIOD peripheral. */

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Disable all interrupts. */

    BSP_IntDisAll();

    /* OS initialization. */

    OSInit(&oseError);

    OSTaskCreate((OS_TCB       *)&AppTaskStartTCB,
                 (CPU_CHAR     *)"App Task Start",
                 (OS_TASK_PTR   )AppTaskStart, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_START_PRIO,
                 (CPU_STK      *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE  )AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE / 10],
                 (CPU_STK_SIZE  )APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&oseError);

/*  Exemple de creation de tache :
 * 	OSTaskCreate((OS_TCB       *)&AppTaskStartTCB,
                 (CPU_CHAR     *)"App Task Start",
                 (OS_TASK_PTR   )AppTaskStart,
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_START_PRIO,
                 (CPU_STK      *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE  )AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE / 10],
                 (CPU_STK_SIZE  )APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&oseError);
                 */
    OSTaskCreate((OS_TCB       *)&buttonTCB,
                 (CPU_CHAR     *)"TI bouton",
                 (OS_TASK_PTR   )buttonTask,
                 (void         *)0,
                 (OS_PRIO       )BUTTON_TASK_PRIO,
                 (CPU_STK      *)&buttonSTK[0],
                 (CPU_STK_SIZE  )buttonSTK[BUTTON_STK_SIZE / 2],
                 (CPU_STK_SIZE  )BUTTON_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&oseError);
    /* Start multitasking. */

    OSStart(&oseError);

    (void)&oseError;
    
    return(0);
}

static void AppTaskStart(void *p_arg) {

	OS_ERR	oseError;

	(void)p_arg;

	/* Initialize BSP functions. */

	BSP_Init();

	/* Initialize the uC/CPU services. */

	CPU_Init();

	/* Start tick initialization. */

	BSP_Tick_Init();

	/* Initialize memory management module. */

	Mem_Init();

	/* Initialize mathematical module. */

	Math_Init();

#if OS_CFG_STAT_TASK_EN > 0u

	/* Compute CPU capacity with no task running. */

	OSStatTaskCPUUsageInit(&oseError);

#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN

	CPU_IntDisMeasMaxCurReset();

#endif

    while(DEF_TRUE) {
        GPIOD->ODR ^= GPIO_Pin_15;

        /* Time delay. */
        OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &oseError);
    }
}

void buttonTask(void *p_arg){

}

#define USE_FULL_ASSERT

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
	/* Switch off all leds. */
	GPIOD->BSRRH = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

	while(1) {
		GPIOD->ODR ^= GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

		/* Delay. */
		for(uint32_t i = 0; i < 10000000; i++);
	}
}
#endif
