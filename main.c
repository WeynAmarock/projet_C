#include "iir.h"
#include "define.h"
#include "affichage.h"
#include "mesure.h"
#include "lecture.h"
#include "integration.h"

int main(){
    oxy myOxy;
    int file_state = 0;
    FILE* pf=initFichier("record1_iir.dat");

    //integrationTest("record1.dat");
    myOxy=mesureTest("record1_iir.dat");
    //printf("ACR = %f\t DCR = %f\t ACIR = %f\t DCIR = %f\n", myAbsorp.acr,myAbsorp.dcr,myAbsorp.acir,myAbsorp.dcir);
    finFichier(pf);

    return 0;
}

