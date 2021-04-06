#include "fir.h"

absorp firTest(char* filename)
{

	absorp data;
	absorp myAbsorp;

	// Initialisation du buffer, contient 51 zéros
	absorp circ_buff[51] = {0};

	int i, fileState = 0;


	// nitialisation à 0 les valeurs de acr et acir  
	myAbsorp.acr=0;
	myAbsorp.acir=0;
	

	FILE* file = initFichier(filename);
	
	while(fileState != EOF)
	{
		// Donnée la plus récente
		data = lireFichier(file, fileState);

		// Buffer circulaire // La nouvelle donnée écrase la plus vielle
		for (i = 50; i > 0; i--) 
		{
        	circ_buff[i] = circ_buff[i-1]; // Décalage des données du buffer
    	}

    	// Insertion de la nouvelle donnée // Ecrase la donnée vielle de 51 tours 
    	circ_buff[0] = data;

    	// Filtrage
		for(i=0; i<51; i++)
		{
			myAbsorp.acr += FIR_TAPS[i]*circ_buff[i].acr;
			myAbsorp.acir += FIR_TAPS[i]*circ_buff[i].acir;
		}
	}

	finFichier(file);

	return myAbsorp;
}
