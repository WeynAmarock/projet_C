#include "affichage.h"

void affichage(oxy myOxy){

    //On vérifie si le fichier .verroudata est déja créé 
    if( access( ".verrouData", F_OK ) == -1 )
    {   
        // Le fichier .verroudata n'existe pas, on crée alors ce fichier
        FILE* verrou = NULL;
        verrou = fopen(".verrouData", "w");
        fclose(verrou);

        // On modifie alors Data.txt
        FILE* data = NULL;
 
        data = fopen("Data.txt", "w+");
 
        if (data != NULL)
        {
            fprintf(data,"%d\n%d",myOxy.spo2,myOxy.pouls); 
            fclose(data);
        }
        
        //On enlève le verrou une fois la modification terminé
        remove(".verrouData");
    }
		
}

