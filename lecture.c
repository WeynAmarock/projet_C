#include "lecture.h" 

//IN : FILE * et un int *
//OUT : absorp 
//Cette fonction récupère les valeurs d'un absorp et le retourne  
absorp lecture(FILE* file_pf, int* file_state){

	// On initialise les donnees 
	absorp myAbsorp = initAbsorp();

	int dix=1000;	// Cette variable sert à calculer les valeurs du absorp à la bonne puisence de dix
	int etat =0;	// Cette varaible sert à placer les valeurs trouvé à la bonne place dans le absorp 
	//(etat = 0 => acr, etat = 1 => dcr, etat = 2 => acir, etat = 3 => dcir)
	int chiffre;	//Cette variable sert à remplacer la valeur récupérer dans la trame qui est en hexa pour la convertir en decimal ( 0x32 => 2)
	int i=0;		//compteur utilisé dans les for
	char carac;		//Variable qui stoque l'octet que l on lit dans la trame 
	char trame[21]={0};		// Variable contenant les octets d'informations


	// Les trames sont envoye par packet de 21 octets
	// S il y a un probleme dans la trame, alors sa taille sera differente de 21  
	// S il y a un probleme, alors on abandone la trame actuelle pour la remplacer par la suivante 
	while(i!=20){
		i=0;
		//Chaque trames sont separees par un 0x0d
		while((carac=fgetc(file_pf))!=0x0d){ 
			if(carac==EOF){
				*file_state = EOF;
				return myAbsorp;
			}
			trame[i] = carac; 
			i++;
		}
	}
			

	//On calcule les valeurs du absorp avec la trame recuperee
	for(i=0; i<sizeof(trame);i++){
		// Chaque valeur d'un absorp est composé de 4 octets
		// Lesvaleurs d'absorp contenu dans la trame sont separes par un ; (= 0x0F)
		// A chaque ;, on modifie etat pour changer de variable à modifier
		if(trame[i] != 0x2c ){
			//On recupère la valeur en dec que l on stocke dans chiffre
			chiffre = trame[i] & 0x0F;
			switch(etat){
				case 0:
					myAbsorp.acr = myAbsorp.acr + chiffre *dix;
					break;
				case 1:
					myAbsorp.dcr=myAbsorp.dcr + chiffre *dix;
					break;
					myAbsorp.acir = myAbsorp.acir + chiffre *dix;
					break;
				case 3 :
					myAbsorp.dcir=myAbsorp.dcir + chiffre *dix;
					break;
			}
			dix=dix/10;
		}else{
			etat++;
			dix = 1000;
		}
	}
	// On recadrer les 2 composantes alternatives (ACR et ACIR) autour de 0
	myAbsorp.acr =myAbsorp.acr-2048;
	myAbsorp.acir =myAbsorp.acir-2048;
	return myAbsorp;	
}


//Cette fonction initialise a 0 le absorp donnee en parametre et le retourne 
absorp initAbsorp(void){
	absorp myAbsorp;
	myAbsorp.acr=0;
	myAbsorp.acir=0;
	myAbsorp.dcr=0;
	myAbsorp.dcir=0;
	return myAbsorp;
}


