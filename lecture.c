#include "lecture.h"


absorp lecture(FILE* file_pf, int* file_state){

	absorp myAbsorp = initAbsorp();

	int a=1000;
	int etat =0;
	int chiffre;
	int i=0;
	int cpt = 0;
	char carac;
	char trame[21]={0};

	//On récupère une trame 
	while(i!=20){
		i=0;
		while((carac=fgetc(file_pf))!=0x0d){ 
			if(carac==EOF){
				*file_state = EOF;
				return myAbsorp;
			}
			trame[i] = carac; 
			i++;
		}
	}
			

	//On calcule les valeurs 
	for(i=0; i<sizeof(trame);i++){
		if(trame[i] != 0x2c ){
			chiffre = trame[i] & 0x0F;
			switch(etat){
				case 0:
					myAbsorp.acr = myAbsorp.acr + chiffre *a;
					break;
				case 1:
					myAbsorp.dcr=myAbsorp.dcr + chiffre *a;
					break;
				case 2:
					myAbsorp.acir = myAbsorp.acir + chiffre *a;
					break;
				case 3 :
					myAbsorp.dcir=myAbsorp.dcir + chiffre *a;
					break;
			}
			a=a/10;
		}else{
			etat++;
			cpt ++;
			a = 1000;
		}
	}

	myAbsorp.acr =myAbsorp.acr-2048;
	myAbsorp.acir =myAbsorp.acir-2048;
	return myAbsorp;	
}



absorp initAbsorp(void){
	absorp myAbsorp;
	myAbsorp.acr=0;
	myAbsorp.acir=0;
	myAbsorp.dcr=0;
	myAbsorp.dcir=0;
	return myAbsorp;
}



int verif_trame(char *tab){
	int i = 0;
	for(i = 0; i < sizeof(tab); i++){
		switch(i){
			case 4:
			case 9:
			case 14:
				if(tab[i]!=0x2c){
					return 0;
				}
				break;
			case 19 :			
			 	if(tab[i]!=0x0a){
					return 0;
				}
			 	break;
			case 20 :
			 	if(tab[i]!=0x0d){
					return 0;
				}
				break;
		}
	}
	return 1;
}

