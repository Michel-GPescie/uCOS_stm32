#ifndef __PERSONNAL_SOURCES__
#define __PERSONNAL_SOURCES__

#include <includes.h>

#define BLINK_INF_PRIO	4u
#define BLINK_R2C_PRIO	3u

#define BLINK_TASK_STK_SIZE 256u

OS_TCB	led_blink_infTCB;
OS_TCB	led_blink_r2cTCB;

CPU_STK  led_blink_infStk[BLINK_TASK_STK_SIZE];
CPU_STK  led_blink_r2cStk[BLINK_TASK_STK_SIZE];

void led_blink_inf(void *p_arg);
void led_blink_r2c(void *p_arg);

#endif /* __PERSONNAL_SOURCES__ */
