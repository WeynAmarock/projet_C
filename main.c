#include "iir.h"
#include "define.h"
#include "affichage.h"
#include "mesure.h"
#include "lecture.h"

int main(){
    absorp myAbsorp;
    int file_state = 0;
    FILE* pf=initFichier("record1_bin.dat");


    do{
		  myAbsorp = lecture(pf,&file_state);

	  }while(file_state != EOF);

   /* for(int i=0;i<21;i++){
      printf("%x\n",fgetc(pf));
    }*/
   
   /*myAbsorp = lecture(pf,file_state);
   printf("ACR = %f\t DCR = %f\t ACIR = %f\t DCIR = %f\n", myAbsorp.acr,myAbsorp.dcr,myAbsorp.acir,myAbsorp.dcir);
   myAbsorp = lecture(pf,file_state);
   printf("ACR = %f\t DCR = %f\t ACIR = %f\t DCIR = %f\n", myAbsorp.acr,myAbsorp.dcr,myAbsorp.acir,myAbsorp.dcir);
   myAbsorp = lecture(pf,file_state);*/

    printf("ACR = %f\t DCR = %f\t ACIR = %f\t DCIR = %f\n", myAbsorp.acr,myAbsorp.dcr,myAbsorp.acir,myAbsorp.dcir);
    finFichier(pf);

    return 0;
}

