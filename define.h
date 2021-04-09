#ifndef DEFINE_H
#define DEFINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



/*! ------------------------------------------------------------
  
  \struct absorp
 
  \brief measures
  
  ------------------------------------------------------------*/

typedef struct{
		float acr;  /*!< AC R */
		float dcr;  /*!< DC R */
		float acir;  /*!< AC IR */
		float dcir;  /*!< DC IR */
	} absorp;

/*! ------------------------------------------------------------
  
  \struct oxy
 
  \brief   
  
  ------------------------------------------------------------*/

typedef struct{
		int spo2;  /*!< SPO2 */
		int pouls;  /*!< Pouls */
	} oxy;


typedef struct{
		int cpt_pouls; //Compteur du nombre de données (de absorp) dans une période
		int cpt_periode;
		float val_maxR, val_maxIR, val_minR,val_minIR; //Valeur max et min de acr et acir 
		int state; // = 1 si période en cours ou = 0 si prériode terminée
		float last_value; // Derière valeur en mémoire
		float ptp_ACr;
		float ptp_ACir;
		int pouls;
	} periode;


#endif // DEFINE_H
