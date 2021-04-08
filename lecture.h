#include "define.h"
#include "fichiers.h"

absorp lecture(FILE* file_pf, int* file_state);

absorp initAbsorp(void);

int verif_trame(char *tab);

char * take_trame(char *tab,FILE *file_pf,int *file_state);
