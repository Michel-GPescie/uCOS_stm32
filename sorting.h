/* * * * * * * * * * * * * * * * * * * * * * * * *
 * 												 *
 * Projet Temps Reel - Polytech Montpellier		 *
 * 		Alexandre Cazaux						 *
 * 		Michel Gomez-Pescie						 *
 * 		Fevrier 2015							 *
 * 												 *
 * file: sorting.h								 *
 * 												 *
 * * * * * * * * * * * * * * * * * * * * * * * * *
 */


#ifndef __SORTING_H__
#define __SORTING_H__

#include  <app_cfg.h>
#include  <includes.h>
#include <pinmap.h>


/* Semaphores ---------------------------------------------------------------------------*/
OS_SEM Sem0to1;
OS_SEM SemFinLigne;
OS_SEM Sem1to2;
OS_SEM Sem1to3;
OS_SEM Sem2to4;
OS_SEM Sem4to2;
OS_SEM Sem2to5;
OS_SEM SemtoA4;
OS_SEM Sem3to6;
OS_SEM Sem2to6;

/* Flag group ---------------------------------------------------------------------------*/
#define SENSOR_0 (OS_FLAGS)0x0001
#define SENSOR_1 (OS_FLAGS)0x0002
#define SENSOR_2 (OS_FLAGS)0x0004
#define SENSOR_3 (OS_FLAGS)0x0008
#define SENSOR_4 (OS_FLAGS)0x0010
#define SENSOR_5 (OS_FLAGS)0x0020
#define SENSOR_6 (OS_FLAGS)0x0040
#define SENSOR_7 (OS_FLAGS)0x0080
#define SENSOR_8 (OS_FLAGS)0x0100
#define SENSOR_9 (OS_FLAGS)0x0200
#define SENSOR_10 (OS_FLAGS)0x0400
OS_FLAG_GRP inputs;

/**	Chaque tache aura les elements suivants:
 *  #define:
 * 		* une dimension de stack
 * 		* une priorité
 * 	declaration:
 * 		* un Task Control Block (OS_TCB)
 * 		* une stack (CPU_STK)
 * 		* le prototype de la tache
 * 		* la tache dans le *.c
 *
 */

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * *		Tapis entree		 * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */
#define TAPIS_ENTREE_STK_SIZE 128u
#define TAPIS_ENTREE_PRIO	10u

OS_TCB tapisEntreeTCB;
CPU_STK tapisEntreeSTK[TAPIS_ENTREE_STK_SIZE];

void tapisEntreeTask(void *p_arg);

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * *		Tapis transfert		 * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */
#define TAPIS_TRANSFERT_STK_SIZE 128u
#define TAPIS_TRANSFERT_PRIO	10u

OS_TCB tapisTransfertTCB;
CPU_STK tapisTransfertSTK[TAPIS_TRANSFERT_STK_SIZE];

void tapisTransfertTask(void *p_arg);

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * *			Tri		 		 * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */
#define TRI_STK_SIZE 128u
#define TRI_PRIO	10u

OS_TCB triTCB;
CPU_STK triSTK[TRI_STK_SIZE];

void triTask(void *p_arg);


/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * *			Rotor			 * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */
#define ROTOR_STK_SIZE 128u
#define ROTOR_PRIO	9u

OS_TCB rotorTCB;
CPU_STK rotorSTK[TAPIS_ENTREE_STK_SIZE];

void rotorTask(void *p_arg);

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * *		Evacuation Gauche	 * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */
#define EVAC_GAUCHE_STK_SIZE 128u
#define EVAC_GAUCHE_PRIO	8u

OS_TCB evacGaucheTCB;
CPU_STK evacGaucheSTK[EVAC_GAUCHE_STK_SIZE];

void evacGaucheTask(void *p_arg);

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * *		Evacuation Droite	 * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */
#define EVAC_DROITE_STK_SIZE 128u
#define EVAC_DROITE_PRIO	8u

OS_TCB evacDroiteTCB;
CPU_STK evacDroiteSTK[EVAC_DROITE_STK_SIZE];

void evacDroiteTask(void *p_arg);

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * *		Scrutation des In.	 * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */
#define INPUT_SCRUT_STK_SIZE 128u
#define INPUT_SCRUT_PRIO 4u

OS_TCB inputScrutTCB;
CPU_STK inputScrutSTK[INPUT_SCRUT_STK_SIZE];

void inputScrutationTask(void *p_arg);

#endif /*	__SORTING_H__	*/
