#include "fir.h"

absorp firTest(char* filename)
{

	absorp data;	
	absorp myAbsorp;
	int fileState = 0;


	// Initialisation du buffer, contient 51 zéros
	absorp circ_buff[51] = {0};

	FILE* file = initFichier(filename);

	do {

		// Donnée la plus récente
		data = lireFichier(file, &fileState);

		if(fileState!= EOF) 
		{
	
			// Appelle fonction FIR // Retourne absorp filtré
			myAbsorp = FIR(data, circ_buff);
		}
	} while(fileState != EOF);
	

	finFichier(file);

	return myAbsorp;
}


absorp FIR(absorp data, absorp* circ_buff)
{
	int i;
	absorp myAbsorp;

	float FIR_TAPS[51]={
	    1.4774946e-019,
	    1.6465231e-004,
	    3.8503956e-004,
	    7.0848037e-004,
	    1.1840522e-003,
	    1.8598621e-003,
	    2.7802151e-003,
	    3.9828263e-003,
	    5.4962252e-003,
	    7.3374938e-003,
	    9.5104679e-003,
	    1.2004510e-002,
	    1.4793934e-002,
	    1.7838135e-002,
	    2.1082435e-002,
	    2.4459630e-002,
	    2.7892178e-002,
	    3.1294938e-002,
	    3.4578348e-002,
	    3.7651889e-002,
	    4.0427695e-002,
	    4.2824111e-002,
	    4.4769071e-002,
	    4.6203098e-002,
	    4.7081811e-002,
	    4.7377805e-002,
	    4.7081811e-002,
	    4.6203098e-002,
	    4.4769071e-002,
	    4.2824111e-002,
	    4.0427695e-002,
	    3.7651889e-002,
	    3.4578348e-002,
	    3.1294938e-002,
	    2.7892178e-002,
	    2.4459630e-002,
	    2.1082435e-002,
	    1.7838135e-002,
	    1.4793934e-002,
	    1.2004510e-002,
	    9.5104679e-003,
	    7.3374938e-003,
	    5.4962252e-003,
	    3.9828263e-003,
	    2.7802151e-003,
	    1.8598621e-003,
	    1.1840522e-003,
	    7.0848037e-004,
	    3.8503956e-004,
	    1.6465231e-004,
	    1.4774946e-019
	};


	// Initialisation à 0 les valeurs de acr et acir  
	myAbsorp.acr = 0;
	myAbsorp.acir = 0;

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

	myAbsorp.dcr = data.dcr;
	myAbsorp.dcir = data.dcir;

	
	return myAbsorp;
}
