// #include "integration.h"


// void integrationTest(char* filename)
// {
// 	int fileState = 0;
// 	int compteur = 0;

// 	absorp myAbsorp;
// 	absorp x;
// 	absorp y;
// 	absorp old_x;

// 	myAbsorp.acr=0;
// 	myAbsorp.acir=0;

// 	old_x.acr=0;
// 	old_x.acir=0;
// 	y.acr=0;
// 	y.acir=0;

// 	oxy myOxy;
// //	int i = 0;

// 	periode myPeriode;
// 	initPeriode(&myPeriode);

// 	// Initialisation du buffer, contient 51 zéros
// 	absorp circ_buff[51] = {0};

	

// 	FILE* file = initFichier(filename);

// 	do {
//     //printf("\n\tSTART\n");
//     //printf("cpt periode = %d\n",myPeriode.cpt_periode);
// 		myAbsorp = lireFichier(file, &fileState);

// 		if (fileState != EOF) {

// 			x = FIR(myAbsorp, circ_buff);			// absorp FIR(absorp data, absorp* circ_buff)

// 			y = IIR(x, old_x, y);		// absorp IIR(absorp x,absorp old_x, absorp old_y)

// 			old_x = x;
			

// 			mesure(y, &myPeriode, &myOxy);			// void mesure(absorp myAbsorp ,periode *myPeriode, oxy *myOxy)
			
			
// 			//printf("%d\n", i);
// 			//i++;
//       if(!myPeriode.state){
//         // printf("pouls > %d\t\t\t< MESURE\n", myOxy.pouls);
// 			  // printf("spo2 > %d\t\t\t< MESURE\n\n", myOxy.spo2);
//         affichage(myOxy);			// void affichage(oxy myOxy)
//       }	
// 		}

// 	} while (fileState != EOF);


// 	finFichier(file);
// }

#include "integration.h"


void integrationTest(char* filename)
{    
    int fileState = 0;
    int compteur = 0;

    absorp myAbsorp;
    absorp x;
    absorp y;
    absorp old_x;

    myAbsorp.acr=0;
    myAbsorp.acir=0;

    old_x.acr=0;
    old_x.acir=0;
    y.acr=0;
    y.acir=0;

    oxy myOxy;

    //int i = 0;

    periode myPeriode;

    initPeriode(&myPeriode);

    // Initialisation du buffer, contient 51 zéros
    absorp circ_buff[51] = {0};

    
    FILE* file = initFichier(filename);

    do {

        myAbsorp = lireFichier(file, &fileState);

        if (fileState != EOF) {

            x = FIR(myAbsorp, circ_buff);            // absorp FIR(absorp data, absorp* circ_buff)

            y = IIR(x, old_x, y);        // absorp IIR(absorp x,absorp old_x, absorp old_y)

            old_x = x;
            
            mesure(y, &myPeriode, &myOxy);            // void mesure(absorp myAbsorp ,periode *myPeriode, oxy *myOxy)

            //printf("%d\n", i);
            //i++;
            //printf("pouls > %d\t\t\t< MESURE\n", myOxy.pouls);
            //printf("spo2 > %d\t\t\t< MESURE\n", myOxy.spo2);

            
            affichage(myOxy);            // void affichage(oxy myOxy)    
            
            
        }

    } while (fileState != EOF);


    finFichier(file);
}

