#include "lecture.h"


absorp lecture(FILE* file_pf, int* file_state){

	absorp myAbsorp = initAbsorp();

	//int val; 
	//int cpt =0;
	//int a=1000;
	//int etat =0;
	//int chiffre;

	char tab[21]={0};
	char carac;

	for(int i=0;i<21;i++){
		carac=fgetc(file_pf);
		if(carac==EOF){
			*file_state = EOF;
			return myAbsorp;
		}
		tab[i] = carac; 
	}
	
    do{
		val = fgetc(file_pf);
		printf("val = %x\n",val);
		//* file_state = val ;
		// chiffre = val & 0x0F;


		if(val == 0x0a){
			myAbsorp.acr = myAbsorp.acr - 2048;
			myAbsorp.acir = myAbsorp.acir - 2048;
			file_test=file_pf;
			if(fgetc(file_test)!=EOF){
				*file_state=1;
			}
			//printf("cpt = %d\n",cpt);
			return myAbsorp;
		}

		// if(val != 0x2c){
		// 	switch(etat){
		// 		case 0:
		// 			myAbsorp.acr = myAbsorp.acr + chiffre *a;
		// 			break;
		// 		case 1:
		// 			myAbsorp.dcr=myAbsorp.dcr + chiffre *a;
		// 			break;
		// 		case 2:
		// 			myAbsorp.acir = myAbsorp.acir + chiffre *a;
		// 			break;
		// 		case 3 :
		// 			myAbsorp.dcir=myAbsorp.dcir + chiffre *a;
		// 			break;
		// 	}
			a=a/10;		
		}else{
			etat++;
			a= 1000;
		}
		//cpt++;	
    }while(val != EOF);	
	//printf("\n");
	//return myAbsorp;
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
	//for(int i = 0; i)
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