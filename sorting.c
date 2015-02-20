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
				if(GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_0)==1)	{
					Etat_0 = P5;
					OSTaskSemPost(&Sem0to1, OS_OPT_POST_1, &err);
				} else {
					OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
				}
				break;
			case P5:
				if (GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_0)==0) {
					Etat_0 = P8;
					GPIO_SetBits(IDI_SLOT1_PORT, IDI_0);
				} else {
					OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
				}
				break;
			case P8:
				OSSemPend(&SemFinLigne, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
				Etat_0 = P4;
				// /!\ logique inversee: mettre le bit � 0 enclenche l'actionneur, 1 le stoppe
				GPIO_ResetBits(IDI_SLOT1_PORT, IDI_0);
				break;
			default:
				break;
				// On a un pb, reste a voir comment implementer une IHM.
		}
	}
}

void tapisTransfertTask(void *p_arg)	{
	OS_ERR err;
	CPU_TS ts;
	(void)p_arg;

	enum tapis_1{
		Init,
		A1a,
		A1b,
		A1c
	};

	int etat_1=Init;

	while(DEF_TRUE) {

		switch (etat_1)
		{
			case Init :
				OSSemPend(&Sem0to1,
						  0,
						  OS_OPT_PEND_BLOCKING,
						  &ts,
						  &err);

				etat_1 = A1a;
				GPIO_ResetBits(IDI_SLOT1_PORT,IDI_1);
				break;

			case A1a :
				if(GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_2)==1)
				{
					OSSemPost(&Sem1to3,
								  OS_OPT_POST_1,
								  &err);
					etat_1=A1b;
				}
				else if ((GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_1)==1) && (GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_2)==0))
				{
					OSSemPost(&Sem1to2,
								  OS_OPT_POST_1,
								  &err);
					etat_1=A1b;
				}
				else
				{
					OSTimeDlyHMSM(0,0,0,1,OS_OPT_TIME_HMSM_STRICT, &err);
				}
				break;

			case A1b :
				if(GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_3)==1)
						etat_1=A1c;
				break;
			case A1c :
				if(GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_3)==0)
				{
					GPIO_SetBits(IDI_SLOT1_PORT,IDI_1);
					etat_1=Init;
				}
				else
				{
					OSTimeDlyHMSM(0,0,0,1,OS_OPT_TIME_HMSM_STRICT, &err);
				}
				break;
			Default:
				break;
		}
	}

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
