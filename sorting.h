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
OS_SEM Sem2to5;
OS_SEM Sem2to6;


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
#define ROTOR_PRIO	10u

OS_TCB rotorTCB;
CPU_STK rotorSTK[TAPIS_ENTREE_STK_SIZE];

void rotorTask(void *p_arg);

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * *		Evacuation Gauche	 * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */
#define EVAC_GAUCHE_STK_SIZE 128u
#define EVAC_GAUCHE_PRIO	10u

OS_TCB evacGaucheTCB;
CPU_STK evacGaucheSTK[EVAC_GAUCHE_STK_SIZE];

void evacGaucheTask(void *p_arg);

/* * * * * * * * * * * * * * * * * * * * * * */
/* * * * *		Evacuation Droite	 * * * * */
/* * * * * * * * * * * * * * * * * * * * * * */
#define EVAC_DROITE_STK_SIZE 128u
#define EVAC_DROITE_PRIO	10u

OS_TCB evacDroiteTCB;
CPU_STK evacDroiteSTK[EVAC_DROITE_STK_SIZE];

void evacDroiteTask(void *p_arg);

#endif /*	__SORTING_H__	*/
