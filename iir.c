#include "iir.h"

absorp iirTest(char* filename){
	absorp	myAbsorp, x, old_x;
	//On initialise à 0 les valeurs de acr et acir  
	myAbsorp.acr=0;
	myAbsorp.acir=0;
	old_x.acr=0;
	old_x.acir=0;
	int fileState = 0;

	FILE* pf=initFichier(filename);

	do{
		x = lireFichier(pf,&fileState); // x prend la valeur du nouvelle absorp du fichier
		myAbsorp=IIR(x,old_x,myAbsorp);	// On filtre la valeur de x 
		old_x=myAbsorp; //On remplace la valeur de old_x par x

	}while(fileState != EOF);

	finFichier(pf);
	return myAbsorp;
}


absorp IIR(absorp x,absorp old_x, absorp old_y){
	absorp myAbsorp;
	myAbsorp.acr = x.acr - old_x.acr + ALPHA * old_y.acr;
	myAbsorp.acir = x.acir - old_x.acir + ALPHA * old_y.acir;
	myAbsorp.dcr = x.dcr;
	myAbsorp.dcir = x.dcir;
	return myAbsorp;
}