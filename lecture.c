#include "lecture.h"


absorp lecture(FILE* file_pf, int* file_state){

	absorp myAbsorp = initAbsorp();

	int a=1000;
	int etat =0;
	int chiffre;

	char tab[21]={0};
	char carac;
	int i;

	for(i=0;i<21;i++){
		carac=fgetc(file_pf);
		//printf("%x ", carac);
		if(carac==EOF){
			*file_state = EOF;
			return myAbsorp;
		}
		tab[i] = carac; 
	}

	// On vérifie que la trame envoyé est correcte 
	//printf("%d\n",verif_trame(tab));
	while(!verif_trame(tab)){ 

		//On remplace la deriere valeur par une nouvelle entrée que l on place a la première place 
		for (i = 20; i > 0; i--) {
    		tab[i] = tab[i-1]; // Décalage des donnees du buffer
		}
		carac=fgetc(file_pf);
		if(carac==EOF){
			*file_state = EOF;
			return myAbsorp;
		}
		
		tab[0] = carac; 
	}

	for(i=0; i<21;i++){
		
		if(tab[i] == 0x0a){
			chiffre = tab[i] & 0x0F;
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
			a = 1000;
		}
	}

	// *file_state=1;
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
	for(i = 0; i < 21; i++){
		switch(i){
			case 4:
			case 9:
			case 14:
				if(tab[i]!=0x2c){
					//printf("test , %d => %c\n",i,tab[i]);
					return 0;
				}
				break;
			case 19 :
			case 20 :			
			 	if(tab[i]!=0x0a){
					//printf("test 0x0a %d\n",i);
					return 0;
				}
				break;
			// case 20 :
			//  	if(tab[i]!=0x0d){
			// 		 //printf("test 0x0a %d\n",i);
			// 		return 0;
			// 	}
			// 	break;
		}
	}
	return 1;
}

/*printf("%d\n",*file_state);
	char x,y;
	int a=0,b=0,c=0,d=0;
	*file_state=fscanf(file_pf,"%d,%d,%d,%d%c%c",&a,&b,&c,&d,&x,&y);
	myAbsorp.acr=a;
	myAbsorp.dcr=b;
	myAbsorp.acir=c;
	myAbsorp.dcir=d;
	myAbsorp.acr=myAbsorp.acr - 2048;
	myAbsorp.acir=myAbsorp.acir - 2048;*/