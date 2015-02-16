#include <blink.h>

/*		PERSONNAL TASKS		*/
void led_blink_inf(void *p_arg){
	OS_ERR err;

	while(DEF_ON){
		GPIOD->ODR ^= GPIO_Pin_14;
        OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}
void led_blink_r2c(void *p_arg){
	OS_ERR err;

	GPIOD->ODR ^= GPIO_Pin_13;

	OSTaskDel((OS_TCB *)0, &err);
}
