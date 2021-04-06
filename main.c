#include "iir.h"
#include "define.h"
#include "affichage.h"

int main(){
    oxy myOxy;
    myOxy.spo2= 100;
    myOxy.pouls = 50;
    affichage(myOxy);
    return 0;
}