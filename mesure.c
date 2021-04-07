#include "mesure.h"

oxy mesureTest(char* filename){
	oxy myOxy;
	absorp data;
	int fileState = 0;
	periode *myPeriode;
	myPeriode = malloc(1*sizeof(periode));

	//On initialise MyPeriode
	initPeriode(myPeriode);

	FILE* pf=initFichier(filename);

	do{
		data = lireFichier(pf,&fileState); // data prend la valeur du nouvelle absorp du fichier
		mesure(data,myPeriode);
		
	}while(fileState != EOF);

	free(myPeriode);
	finFichier(pf);
	return myOxy;
}


/*
int status_State(int val,  int state)
{
	if(state == 1){
		if(val>200){
			state=2;	
		}
	}
	if(state == 2){
		if(val<200){
			state=3;			
		}
	}
	if(state == 3){
		if(val>200){
			state=4;
		}
	}
	return state;
}*/
	



oxy mesure(absorp myAbsorp ,periode *myPeriode)
{
	oxy myOxy;
	float ratio;
	int ptp_ACr;
	int ptp_ACir;

	//On regarde si on a terminé la période.
	if(myAbsorp.acr>0 && myPeriode->last_value<0){

		ptp_ACr=myPeriode->val_maxR - myPeriode->val_minR;
		ptp_ACir=myPeriode->val_maxIR - myPeriode->val_minIR;
		ratio = (ptp_ACr/myAbsorp.dcr)/(ptp_ACir/myAbsorp.dcir);

		if(ratio<=1){
			myOxy.spo2= -25 * ratio  +110;
		}else{
			myOxy.spo2= -35 * ratio  +120;
		}
		myOxy.pouls=30000/myPeriode->cpt_pouls;
		
		initPeriode(myPeriode);
		return myOxy;
	}

	if(myAbsorp.acr>0){
		myPeriode->val_maxR=val_sup(myAbsorp.acr,myPeriode->val_maxR);
	}
	if(myAbsorp.acr<0){
		myPeriode->val_minR=val_inf(myAbsorp.acr,myPeriode->val_minR);
	}
	if(myAbsorp.acir>0){
		myPeriode->val_maxIR=val_sup(myAbsorp.acir,myPeriode->val_maxIR);
	}
	if(myAbsorp.acir<0){
		myPeriode->val_minIR=val_inf(myAbsorp.acr,myPeriode->val_minIR);
	}
	
	myPeriode->last_value=myAbsorp.acr;
	myPeriode->cpt_pouls++;

	//myOxy.spo2=

	//myOxy.pouls= 30000 / cpt;

	return myOxy;
}


int val_inf(int val, int min)
{
	if(val<min){
		return val;
	}else{
		return min;
	}
}

int val_sup(int val, int max)
{
	if(val>max){
		return val;
	}else{
		return max;
	}
}

void initPeriode(periode *myPeriode)
{
	myPeriode->cpt_pouls=0;
	myPeriode->val_maxR=0;
	myPeriode->val_minR=0;
	myPeriode->val_maxIR=0;
	myPeriode->val_minIR=0;
	myPeriode->state=0;
	myPeriode->last_value=0;
}