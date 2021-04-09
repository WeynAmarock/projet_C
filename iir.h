#include "define.h"
#include "fichiers.h"

#define ALPHA 0.992

//Fonction test du filtre IIR
absorp iirTest(char* filename);

//Cette fonction sert à supprimer la composante continue résultante des valeurs retournees par la fonction FIR
absorp IIR(absorp x,absorp old_x, absorp old_y);
