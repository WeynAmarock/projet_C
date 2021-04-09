#include "affichage.h"

//La fonction affichage permet d afficher les informations du pous et du spo2 retourrnes par la fonction mesure 
void affichage(oxy myOxy){
    // Si le fichier .verrouData existe alors ca signifie qu'un ecriture/lecture a deja lieu, donc nous n'ecrivons rien dans le fichier Data.txt
    if( access( ".verrouData", F_OK ) == -1 )
    {   
        // Le fichier .verroudata n'existe pas, on cree alors ce fichier pour signifier qu'une ecriture a lieu
        FILE* verrou = NULL;
        verrou = fopen(".verrouData", "w");
        fclose(verrou);

        // On modifie alors Data.txt
        FILE* data = NULL;

         // On ouvre le fichier Data.txt et on supprime ce qu'il y a à l interieur 
        data = fopen("Data.txt", "w+"); 
 
        if (data != NULL)
        {
            fprintf(data,"%d\n%d",myOxy.spo2,myOxy.pouls); // On ecrit dans le fichier Data.txt le spo2 et le pouls
            fclose(data);
        }
        
        //On enlève le verrou une fois la modification terminé
        remove(".verrouData");
    }
		
}

