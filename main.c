#include  <app_cfg.h>
#include  <includes.h>
#include <sorting.h>
#include <pinmap.h>

/*Queue variable. -----------------------------------------------------------------------*/
OS_Q tapis1totri;
CPU_INT08U flag;

/* Tasks' control blocks. ---------------------------------------------------------------*/

static  OS_TCB   AppTaskStartTCB;

/* Tasks' stack. ------------------------------------------------------------------------*/

static  CPU_STK  AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

/* Tasks. -------------------------------------------------------------------------------*/

static  void  AppTaskStart          (void     *p_arg);
static void initPinmap();

/* Main program. ------------------------------------------------------------------------*/

int main(void) {

	OS_ERR  			oseError;

    /* GPIOD peripheral. */

	initPinmap();

    /* Disable all interrupts. du caca */

    BSP_IntDisAll();

    /* OS initialization. */

    OSInit(&oseError);

    /*Queues*/

    OSQCreate(&tapis1totri,"tapis1totri Queue",2,&oseError);

    /* Semaphores */

    OSSemCreate(&Sem0to1, "semaphore tapis 0 à 1", 0, &oseError);
    OSSemCreate(&SemFinLigne, "semaphore fin de ligne", 0, &oseError);

    OSSemCreate(&Sem1to2, "semaphore tapis 1 à 2", 0, &oseError);
    OSSemCreate(&Sem1to3, "semaphore tapis 1 à 3", 0, &oseError);

    OSSemCreate(&Sem2to4, "semaphore tapis 2 à 4", 0, &oseError);
    OSSemCreate(&Sem4to2, "semaphore tapis 4 à 2", 0, &oseError);
    OSSemCreate(&Sem2to5, "semaphore tapis 2 à 5", 0, &oseError);
    OSSemCreate(&SemtoA4, "semaphore tapis 4 etat intial", 0, &oseError);
    OSSemCreate(&Sem3to6, "semaphore tapis 3 à 6", 0, &oseError);
    OSSemCreate(&Sem2to6, "semaphore tapis 1 à 3", 0, &oseError);

    /* Flag group */

    OSFlagCreate(&inputs, "flag event group", (OS_FLAGS)0, &oseError);

    /* Blink LED :D */
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

    /* tapis 0 */
    OSTaskCreate((OS_TCB       *)&tapisEntreeTCB,
                 (CPU_CHAR     *)"Tapis 0",
                 (OS_TASK_PTR   )tapisEntreeTask,
                 (void         *)0,
                 (OS_PRIO       )TAPIS_ENTREE_PRIO,
                 (CPU_STK      *)&tapisEntreeSTK[0],
                 (CPU_STK_SIZE  )tapisEntreeSTK[TAPIS_ENTREE_STK_SIZE / 10],
                 (CPU_STK_SIZE  )TAPIS_ENTREE_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&oseError);
    /* tapis 1 */
    OSTaskCreate((OS_TCB       *)&tapisTransfertTCB,
                 (CPU_CHAR     *)"Tapis 1",
                 (OS_TASK_PTR   )tapisTransfertTask,
                 (void         *)0,
                 (OS_PRIO       )TAPIS_TRANSFERT_PRIO,
                 (CPU_STK      *)&tapisTransfertSTK[0],
                 (CPU_STK_SIZE  )tapisTransfertSTK[TAPIS_TRANSFERT_STK_SIZE / 10],
                 (CPU_STK_SIZE  )TAPIS_TRANSFERT_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&oseError);
    /* Rotor de tri */
    OSTaskCreate((OS_TCB       *)&triTCB,
                 (CPU_CHAR     *)"Tri",
                 (OS_TASK_PTR   )triTask,
                 (void         *)0,
                 (OS_PRIO       )TRI_PRIO,
                 (CPU_STK      *)&triSTK[0],
                 (CPU_STK_SIZE  )triSTK[TRI_STK_SIZE / 10],
                 (CPU_STK_SIZE  )TRI_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&oseError);
    /* Evacuation vers la gauche */
    OSTaskCreate((OS_TCB       *)&evacGaucheTCB,
                 (CPU_CHAR     *)"Tapis d'evacuation vers la gauche",
                 (OS_TASK_PTR   )evacGaucheTask,
                 (void         *)0,
                 (OS_PRIO       )EVAC_GAUCHE_PRIO,
                 (CPU_STK      *)&evacGaucheSTK[0],
                 (CPU_STK_SIZE  )evacGaucheSTK[EVAC_GAUCHE_STK_SIZE / 10],
                 (CPU_STK_SIZE  )EVAC_GAUCHE_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&oseError);
    /* Evacuation vers la droite */
    OSTaskCreate((OS_TCB       *)&evacDroiteTCB,
                 (CPU_CHAR     *)"Tapis d'evacuation vers la droite",
                 (OS_TASK_PTR   )evacDroiteTask,
                 (void         *)0,
                 (OS_PRIO       )EVAC_DROITE_PRIO,
                 (CPU_STK      *)&evacDroiteSTK[0],
                 (CPU_STK_SIZE  )evacDroiteSTK[EVAC_DROITE_STK_SIZE / 10],
                 (CPU_STK_SIZE  )EVAC_DROITE_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&oseError);
    /* Tâche Rotor */
      OSTaskCreate((OS_TCB       *)&rotorTCB,
                   (CPU_CHAR     *)"Rotor",
                   (OS_TASK_PTR   )rotorTask,
                   (void         *)0,
                   (OS_PRIO       )ROTOR_PRIO,
                   (CPU_STK      *)&rotorSTK[0],
                   (CPU_STK_SIZE  )rotorSTK[EVAC_DROITE_STK_SIZE / 10],
                   (CPU_STK_SIZE  )ROTOR_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&oseError);
      /* gestion des input */
      OSTaskCreate((OS_TCB       *)&inputScrutTCB,
                   (CPU_CHAR     *)"Scrutation Input",
                   (OS_TASK_PTR   )inputScrutationTask,
                   (void         *)0,
                   (OS_PRIO       )INPUT_SCRUT_PRIO,
                   (CPU_STK      *)&inputScrutSTK[0],
                   (CPU_STK_SIZE  )inputScrutSTK[INPUT_SCRUT_STK_SIZE / 10],
                   (CPU_STK_SIZE  )INPUT_SCRUT_STK_SIZE,
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

/*    while(DEF_TRUE) {
        GPIOD->ODR ^= GPIO_Pin_15;
*/
        /* Time delay. */
/*        OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &oseError);
    }*/
}

void initPinmap(){
	GPIO_InitTypeDef  	GPIO_InitStructure;

		// Configure STM32 outputs (USB-4750 inputs)

			// IDI0 to IDI7 on GPIOB

			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

			GPIO_InitStructure.GPIO_Pin = IDI_0 | IDI_1 | IDI_2 | IDI_3 | IDI_4 | IDI_5 | IDI_6 | IDI_7;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_Init(GPIOB, &GPIO_InitStructure);

			// IDI8 to IDI15 on GPIOC

			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

			GPIO_InitStructure.GPIO_Pin = IDI_8 | IDI_9 | IDI_10 | IDI_11 | IDI_12 | IDI_13 | IDI_14 | IDI_15;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_Init(GPIOC, &GPIO_InitStructure);


		// Configure STM32 inputs (USB-4750 outputs)

			// IDO0 to IDO7 on GPIOD

			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

			GPIO_InitStructure.GPIO_Pin = IDO_0 | IDO_1 | IDO_2 | IDO_3 | IDO_4 | IDO_5 | IDO_6 | IDO_7;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_Init(GPIOD, &GPIO_InitStructure);

			// IDO8 to IDO15 on GPIOE

			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

			GPIO_InitStructure.GPIO_Pin = IDO_8 | IDO_9 | IDO_10 | IDO_11 | IDO_12 | IDO_13 | IDO_14 | IDO_15;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_SetBits(IDI_SLOT1_PORT, IDI_0 | IDI_1 | IDI_2 | IDI_3 | IDI_4 | IDI_5 | IDI_6 | IDI_7);
	GPIO_SetBits(IDI_SLOT2_PORT, IDI_8 | IDI_9 | IDI_10 | IDI_11 | IDI_12 | IDI_13 | IDI_14 | IDI_15);
}

#define USE_FULL_ASSERT

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
	/* Switch off all leds. */
/*	GPIOD->BSRRH = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	while(1) {
		GPIOD->ODR ^= GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
*/
		/* Delay. */
/*		for(uint32_t i = 0; i < 10000000; i++);
	}*/
}
#endif
