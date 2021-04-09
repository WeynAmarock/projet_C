#include "mesure.h"


oxy mesureTest(char* filename){

	absorp data;
	int fileState = 0;
	periode *myPeriode;

	myPeriode = malloc(1*sizeof(periode));
	oxy *myOxy ;

	myOxy = malloc(1*sizeof(oxy));
	oxy return_var;

	//On initialise MyPeriode
	initPeriode(myPeriode);

	FILE* pf=initFichier(filename);

	do{
		data = lireFichier(pf, &fileState); // data prend la valeur du nouvelle absorp du fichier
		mesure(data, myPeriode, myOxy);
	}while(fileState != EOF);

	return_var = *myOxy;
	free(myPeriode);
	free(myOxy);
	finFichier(pf);
	return return_var;
}


void mesure(absorp myAbsorp ,periode *myPeriode, oxy *myOxy)
{
	
	float ratio;
	int ptp_ACr;
	int ptp_ACir;
	myPeriode->state=1;
	
	if(!myAbsorp.dcr | !myAbsorp.dcir) {
		//printf("tets return\n");
		return;
	}

	//On regarde si on a terminé la période.
	if(myAbsorp.acr >= 0 && myPeriode->last_value < 0){
		myPeriode->cpt_periode++;
		myPeriode->ptp_ACr = myPeriode->ptp_ACr + ( myPeriode->val_maxR - myPeriode->val_minR);
		myPeriode->ptp_ACir = myPeriode->ptp_ACir + (myPeriode->val_maxIR - myPeriode->val_minIR);

		if(myPeriode->cpt_periode != 2){
			//printf("\ttest mesure 1\n");
			//printf("test jambon \n");
				
			myPeriode->val_maxR=0;
			myPeriode->val_minR=0;
			myPeriode->val_maxIR= 0;
			myPeriode->val_minIR= 0;
		
		}else{
			//printf("\ttest mesure 2\n");
			//printf("test babouin\n");
			//On calcul la valeur moyenne sur les 4 periodes
			myPeriode->ptp_ACr = myPeriode->ptp_ACr / 2; 
			myPeriode->ptp_ACir = myPeriode->ptp_ACir / 2 ;
			//printf("maxR= %d\n",myPeriode->val_maxR);
			//printf("minR= %d\n",myPeriode->val_minR);
	
			ratio = (myPeriode->ptp_ACr/myAbsorp.dcr) / (myPeriode->ptp_ACir/myAbsorp.dcir);

			//printf("acr > %f\nacir > %f\n", myAbsorp.dcr, myAbsorp.dcir);
			// printf("RATIO > %f\n\n", ratio);

			if (ratio<=1){
				myOxy->spo2=-25*ratio+110;
			}else if(ratio>1){
				myOxy->spo2=-35.71*ratio+121.42;
			}else if(ratio>3.4){
				myOxy->spo2=0;
			}else if(ratio<0.4){
				myOxy->spo2=100;
			}

			printf("spo2 = %d\n",myOxy->spo2);

			myPeriode->pouls= 30000/myPeriode->cpt_pouls;
			myOxy->pouls = myPeriode->pouls * 2 ;

			printf("POULS = %d\n",myOxy->pouls);
		
			myPeriode->state=0;
			initPeriode(myPeriode);
			return ;
		}
	}

	if(myAbsorp.acr > 0){
		myPeriode->val_maxR = val_sup(myAbsorp.acr, myPeriode->val_maxR);
		//printf("maxR = %d\n",myPeriode->val_maxR );
	}
	if(myAbsorp.acr < 0){
		myPeriode->val_minR = val_inf(myAbsorp.acr, myPeriode->val_minR);
	}
	if(myAbsorp.acir > 0){
		myPeriode->val_maxIR = val_sup(myAbsorp.acir, myPeriode->val_maxIR);
	}
	if(myAbsorp.acir < 0){
		myPeriode->val_minIR = val_inf(myAbsorp.acr, myPeriode->val_minIR);
	}
	
	myPeriode->last_value = myAbsorp.acr;
	myPeriode->cpt_pouls++;
//printf("cpt POULS = %d\n",myPeriode->cpt_pouls);
	return;
}


int val_inf(int val, int min)
{
	if(val < min){
		return val;
	}else{
		return min;
	}
} 

int val_sup(int val, int max)
{
	if(val > max){
		return val;
	}else{
		return max;
	}
}

void initPeriode(periode *myPeriode)
{
	myPeriode->cpt_pouls = 0;
	myPeriode->cpt_periode = 0;
	myPeriode->val_maxR = 0;
	myPeriode->val_minR = 0;
	myPeriode->val_maxIR =0;
	myPeriode->val_minIR = 0;
	myPeriode->state = 0;
	myPeriode->last_value = 0;
	myPeriode->pouls = 0;
}



// #include "mesure.h"

// oxy mesureTest(char* filename){

// 	absorp data;
// 	int fileState;
// 	periode *myPeriode;

// 	myPeriode = malloc(1*sizeof(periode));
// 	oxy *myOxy ;

// 	myOxy = malloc(1*sizeof(oxy));
// 	oxy return_var;

// 	//On initialise MyPeriode
// 	initPeriode(myPeriode);

// 	FILE* pf=initFichier(filename);

// 	do{
// 		data = lireFichier(pf, &fileState); // data prend la valeur du nouvelle absorp du fichier
// 		mesure(data, myPeriode, myOxy);
// 		printf("POULS => %d\n", myOxy->pouls);
// 		printf("SPO2 => %d\n", myOxy->spo2);
// 	}while(fileState != EOF);
	
// 	return_var = *myOxy;
// 	free(myPeriode);
// 	free(myOxy);
// 	finFichier(pf);
// 	return return_var;
// }


// void mesure(absorp myAbsorp ,periode *myPeriode, oxy *myOxy)
// {
// 	float ratio;
// 	int ptp_ACr;
// 	int ptp_ACir;
	
// 	if(!myAbsorp.dcr | !myAbsorp.dcir) {
// 		return;
// 	}

// 	//On regarde si on a terminé la période.
// 	if(myAbsorp.acr >= 0 && myPeriode->last_value < 0){
		
// 		ptp_ACr = myPeriode->val_maxR - myPeriode->val_minR;
// 		ptp_ACir = myPeriode->val_maxIR - myPeriode->val_minIR;	
// 		ratio = (ptp_ACr/myAbsorp.dcr) / (ptp_ACir/myAbsorp.dcir);

// 		//printf("acr > %f\nacir > %f\n", myAbsorp.dcr, myAbsorp.dcir);
// 		//printf("RATIO > %f\n\n", ratio);

// 		if (ratio<=1){
// 				myOxy->spo2=-25*ratio+110;
// 		}else if(ratio>1){
// 				myOxy->spo2=-35.71*ratio+121.42;
// 		}else if(ratio>3.4){
// 				myOxy->spo2=0;
// 		}else if(ratio<0.4){
// 				myOxy->spo2=100;
// 		}

		
// 		//myOxy->pouls= 30000/myPeriode->cpt_pouls;
// 		myOxy->pouls = (myOxy->pouls + 30000 / myPeriode->cpt_pouls)/2;

// 		initPeriode(myPeriode);
// 	}


// 	if(myAbsorp.acr > 0){
// 		myPeriode->val_maxR = val_sup(myAbsorp.acr, myPeriode->val_maxR);
// 	}
// 	if(myAbsorp.acr < 0){
// 		myPeriode->val_minR = val_inf(myAbsorp.acr, myPeriode->val_minR);
// 	}
// 	if(myAbsorp.acir > 0){
// 		myPeriode->val_maxIR = val_sup(myAbsorp.acir, myPeriode->val_maxIR);
// 	}
// 	if(myAbsorp.acir < 0){
// 		myPeriode->val_minIR = val_inf(myAbsorp.acr, myPeriode->val_minIR);
// 	}
	
// 	myPeriode->last_value = myAbsorp.acr;
// 	myPeriode->cpt_pouls++;
// }


// int val_inf(int val, int min)
// {
// 	if(val < min){
// 		return val;
// 	}else{
// 		return min;
// 	}
// } 

// int val_sup(int val, int max)
// {
// 	if(val > max){
// 		return val;
// 	}else{
// 		return max;
// 	}
// }

// void initPeriode(periode *myPeriode)
// {
// 	myPeriode->cpt_pouls = 0;
// 	myPeriode->val_maxR = 0;
// 	myPeriode->val_minR = 0;
// 	myPeriode->val_maxIR =0;
// 	myPeriode->val_minIR = 0;
// 	myPeriode->state = 0;
// 	myPeriode->last_value = 0;
// }


