#include "iir.h"
#include "define.h"
#include "affichage.h"
#include "mesure.h"

int main(){
    oxy myOxy;
    myOxy = mesureTest("record1_iir.dat");
    return 0;
}