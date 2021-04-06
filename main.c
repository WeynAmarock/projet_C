#include "iir.h"
#include "define.h"

int main(){
    absorp	myAbsorp;
    myAbsorp = iirTest("test_file/record1_fir.dat");
    
    return 0;
}