#include "iir.h"
#include "define.h"
#include "affichage.h"
#include "mesure.h"

int main(){
    oxy myOxy;
    myOxy = mesureTest("record1_iir.dat");
    //printf("spo2 = %d\npouls =  %d\n",myOxy.spo2, myOxy.pouls);
    return 0;
}