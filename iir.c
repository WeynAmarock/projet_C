#include "iir.h"

absorp iirTest(char* filename){
	absorp	myAbsorp, x, old_x;
	//On initialise à 0 les valeurs de acr et acir  
	myAbsorp.acr=0;
	myAbsorp.acir=0;
	old_x.acr=0;
	old_x.acir=0;
	int fileState = 0;
	//On ouvre le fichier de test
	FILE* pf=initFichier(filename);

	do{
		x = lireFichier(pf,&fileState); // x prend la valeur du nouvelle absorp du fichier
		if(fileState != EOF){
			myAbsorp=IIR(x,old_x,myAbsorp);	// On filtre la valeur de x 
			old_x=x; //On remplace la valeur de old_x par x
		}

	}while(fileState != EOF); //On continue cette boucle tant que tout le fichier n a pas ete lu

	finFichier(pf);
	return myAbsorp;
}

//Cette fonction sert à supprimer la composante continue résultante des valeurs retournees par la fonction FIR
//On lui donne en entrée la valeur d'entree retourne par FIR , l'ancienne valeur retournee par FIR et l ancienne valeur retournne par cette fonction
absorp IIR(absorp x,absorp old_x, absorp old_y){
	absorp myAbsorp;
	// La formule est y[n] = x[n] - x[n-1] + alpha * y[n - 1]
	myAbsorp.acr = x.acr - old_x.acr + ALPHA * old_y.acr;
	myAbsorp.acir = x.acir - old_x.acir + ALPHA * old_y.acir;
	//On ne modifie pas la valeur de dcr et dcir 
	myAbsorp.dcr = x.dcr;
	myAbsorp.dcir = x.dcir;
	//On retourne le absorp filtré
	return myAbsorp;
}