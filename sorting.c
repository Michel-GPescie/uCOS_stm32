/* * * * * * * * * * * * * * * * * * * * * * * * *
 * 												 *
 * Projet Temps Reel - Polytech Montpellier		 *
 * 		Alexandre Cazaux						 *
 * 		Michel Gomez-Pescie						 *
 * 		Fevrier 2015							 *
 * 												 *
 * file: sorting.c								 *
 * 												 *
 * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#include "sorting.h"


void tapisEntreeTask(void *p_arg)	{
	OS_ERR err;
	CPU_TS ts;

	enum EtatTapis0 {P4, P5, P8};
	int Etat_0 = P4;
	GPIO_ResetBits(IDI_SLOT1_PORT, IDI_0);

	while(DEF_ON)	{
		switch(Etat_0)
		{
			case P4:
				if(IDO_SLOT1_PORT->IDR & IDO_0)	{
					Etat_0 = P5;
					OSSemPend(&sem0, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
				} else {
					OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_HMSM_STRICT, &oseError);
				}
				break;
			case P5:
				if (!(IDO_SLOT1_PORT->IDR & ID0_0)) {
					Etat_0 = P8;
					GPIO_SetBits(IDI_SLOT1_PORT, IDI_0);
				} else {
					OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_HMSM_STRICT, &oseError);
				}
				break;
			case P8:
				// attente de synchro a implementer
				Etat_0 = P4;
				// /!\ logique inversee: mettre le bit à 0 enclenche l'actionneur, 1 le stoppe
				GPIO_ResetBits(IDI_SLOT1_PORT, IDI_0);
				break;
			default:
				// On a un pb, reste a voir comment implementer une IHM.
		}
	}
}

void tapisTransfertTask(void *p_arg)	{
	OS_ERR err;

}

void triTask(void *p_arg)	{
	OS_ERR err;

}

void rotorTask(void *p_arg)	{
	OS_ERR err;

}

void evacGaucheTask(void *p_arg)	{
	OS_ERR err;

}

void evacDroiteTask(void *p_arg)	{
	OS_ERR err;

}
