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

/*Queue variable. -----------------------------------------------------------------------*/

#include  <app_cfg.h>
#include  <includes.h>
#include <sorting.h>
#include <pinmap.h>

OS_Q tapis1totri;
CPU_INT08U flag;

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
					OSSemPost(&Sem0to1, OS_OPT_POST_1, &err);
				} else {
					OSTimeDlyHMSM(0, 0, 0, 20, OS_OPT_TIME_HMSM_STRICT, &err);
				}
				break;
			case P5:
				if (GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_0)==0) {
					Etat_0 = P8;
					GPIO_SetBits(IDI_SLOT1_PORT, IDI_0);
				} else {
					OSTimeDlyHMSM(0, 0, 0, 20, OS_OPT_TIME_HMSM_STRICT, &err);
				}
				break;
			case P8:
				OSSemPend(&SemFinLigne, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
				Etat_0 = P4;
				// /!\ logique inversee: mettre le bit à 0 enclenche l'actionneur, 1 le stoppe
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

	int etat_1 = Init;

	while(1) {

		switch (etat_1)
		{
			case Init :
				OSSemPend(&Sem0to1,
						  0,
						  OS_OPT_PEND_BLOCKING,
						  &ts,
						  &err);

				GPIO_ResetBits(IDI_SLOT1_PORT,IDI_1);
				etat_1 = A1a;
				break;

			case A1a :
				if(GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_2)==1)
					{
						/*OSSemPost(&Sem1to3,
					                OS_OPT_POST_1,
									&err);*/
						flag='D';
						OSQPost(&tapis1totri,flag,sizeof(flag),OS_OPT_POST_FIFO,&err);
						etat_1=A1b;
					}
					else if ((GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_1)==1) && (GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_2)==0))
					{
						/*OSSemPost(&Sem1to2,
									OS_OPT_POST_1,
									&err);*/
						flag='G';
						OSQPost(&tapis1totri,flag,sizeof(flag),OS_OPT_POST_FIFO,&err);
						etat_1=A1b;
					}
					else
					{
						OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_STRICT,&err);
					}

					break;

			case A1b :
				if(GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_3)==1)
				{
					etat_1=A1c;
					OSSemPost(&Sem1to2,OS_OPT_POST_1,&err);
				}
				break;
			case A1c :
				if(GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_3)==0)
				{
					GPIO_SetBits(IDI_SLOT1_PORT,IDI_1);
					etat_1=Init;
				}
				else
				{
					OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_STRICT, &err);
				}
				break;
			Default:
				break;
		}
	}

}

void triTask(void *p_arg)
{
	OS_ERR err;
	CPU_TS ts;
	char choix_tapis;
	OS_MSG_SIZE size;
	(void)p_arg;

	enum tapis_2_3{
		Init,
		p6,
		p0,
		p37,
		p9,
		p10,
		p11,
		p12};

	int etat_2_3 = Init;

	while(1) {

		switch (etat_2_3)
		{
			case Init :
				if(GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_4)==1)
				{
					OSSemPend(&Sem1to2,
							  0,
							  OS_OPT_PEND_BLOCKING,
							  &ts,
							  &err);
					GPIO_ResetBits(IDI_SLOT1_PORT,IDI_2);
					etat_2_3 = p6;
				}
				break;

			case p6 :
				if(GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_6)==1)
				{
					GPIO_SetBits(IDI_SLOT1_PORT,IDI_2);
					OSSemPost(&Sem2to4, OS_OPT_POST_1, &err);
					if(err==OS_ERR_NONE)
					{
					etat_2_3=p0;}
					else {
						break;
					}
				}
				break;

			case p0:
				//OSSemSet(&Sem2to4, 1, &err);
				OSSemPend(&Sem4to2,
						  0,
						  OS_OPT_PEND_BLOCKING,
						  &ts,
						  &err);
				etat_2_3 = p37;
				break;

			case p37 :
				choix_tapis=OSQPend(&tapis1totri,0,OS_OPT_PEND_BLOCKING,&size,&ts,&err);

				if(choix_tapis=='G')
				{
					etat_2_3=p10;
					GPIO_ResetBits(IDI_SLOT1_PORT,IDI_2);
				}
				if(choix_tapis=='D')
				{
					etat_2_3=p9;
					GPIO_ResetBits(IDI_SLOT1_PORT,IDI_3);
				}
				break;

			case p10:

				if(GPIO_ReadInputDataBit(IDO_SLOT2_PORT, IDO_8)==1)
				{
					OSSemPost(&Sem2to5,
							  OS_OPT_POST_1,
							  &err);
					etat_2_3=p11;
				}
				break;

			case p11:

				if(GPIO_ReadInputDataBit(IDO_SLOT2_PORT, IDO_8)==0)
				{
					OSSemPost(&SemtoA4,
							  OS_OPT_POST_1,
							  &err);
					GPIO_SetBits(IDI_SLOT1_PORT,IDI_2);
					etat_2_3=Init;
				}
				break;

			case p9:

				if(GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_7)==1)
				{
					OSSemPost(&Sem3to6,
							  OS_OPT_POST_1,
							  &err);
					etat_2_3=p12;
				}
				break;
			case p12:

				if(GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_7)==0)
				{
					OSSemPost(&SemtoA4,
							  OS_OPT_POST_1,
							  &err);
					GPIO_SetBits(IDI_SLOT1_PORT,IDI_3);
					etat_2_3=Init;
				}
				break;
			}
		}
}

void rotorTask(void *p_arg)	{
	OS_ERR err;
	CPU_TS ts;
	(void)p_arg;

	enum Rotor{
		p14,
		p7,
		p23
	};

	int etat_4 = p14;

	while(1) {

		switch (etat_4)
		{
			case p14 :
				OSSemPend(&Sem2to4,0, OS_OPT_PEND_BLOCKING, &ts, &err);
				if(err==OS_ERR_NONE)
				{
				GPIO_ResetBits(IDI_SLOT1_PORT,IDI_4);
				etat_4 = p7;
				}else {
					break;
				}
				break;

			case p7 :
				if(GPIO_ReadInputDataBit(IDO_SLOT1_PORT, IDO_5)==1)
				{
					OSSemPost(&Sem4to2,OS_OPT_POST_1,&err);
					etat_4=p23;
				} break;

			case p23 :
				OSSemPend(&SemtoA4,
						  0,
						  OS_OPT_PEND_BLOCKING,
						  &ts,
						  &err);
				GPIO_SetBits(IDI_SLOT1_PORT,IDI_4);
				etat_4=p14;
		}
	}
}

void evacGaucheTask(void *p_arg)	{
	OS_ERR err;
	CPU_TS ts;

	enum tapis_5{
		P20,
		P18,
		P19,
		P29	// ????
	};
	int Etat_5 = P20;
	//GPIO_SetBits(IDI_SLOT1_PORT, IDI_5);

	while(DEF_ON)	{
		switch(Etat_5){
			case P20:
				OSSemPend(&Sem2to5,
						  0,
						  OS_OPT_PEND_BLOCKING,
						  &ts,
						  &err);
				GPIO_ResetBits(IDI_SLOT1_PORT, IDI_5);
				Etat_5 = P18;
				break;
			case P18:
				if(GPIO_ReadInputDataBit(IDO_SLOT2_PORT, IDO_10))	{
					GPIO_ResetBits(IDI_SLOT1_PORT, IDI_5);
					Etat_5 = P19;
				}
				break;
			case P19:
				if(GPIO_ReadInputDataBit(IDO_SLOT2_PORT, IDO_10)==0)	{
					OSSemPost(&SemFinLigne, OS_OPT_POST_1, &err);
					GPIO_SetBits(IDI_SLOT1_PORT, IDI_5);
					Etat_5 = P20;
				}
				break;
			default:
				break;
				/* il y a eu un pepin */

		}
	}
}

void evacDroiteTask(void *p_arg)	{
	OS_ERR err;
	CPU_TS ts;

	enum tapis_6{
		P17,
		P15,
		P16,
		P30	// ????
	};
	int Etat_6 = P17;
	GPIO_SetBits(IDI_SLOT1_PORT, IDI_6);

	while(DEF_ON)	{
		switch(Etat_6){
			case P17:
				OSSemPend(&Sem3to6,
						  0,
						  OS_OPT_PEND_BLOCKING,
						  &ts,
						  &err);
				GPIO_ResetBits(IDI_SLOT1_PORT, IDI_6);
				Etat_6 = P15;
				break;
			case P15:
				if(GPIO_ReadInputDataBit(IDO_SLOT2_PORT, IDO_9))	{
					GPIO_ResetBits(IDI_SLOT1_PORT, IDI_6);
					Etat_6 = P16;
				}
				break;
			case P16:
				if(GPIO_ReadInputDataBit(IDO_SLOT2_PORT, IDO_9)==0)	{
					OSSemPost(&SemFinLigne, OS_OPT_POST_1, &err);
					GPIO_SetBits(IDI_SLOT1_PORT, IDI_6);
					Etat_6 = P17;
				}
				break;
			default:
				break;
				/* il y a eu un pepin */

		}
	}

}
