void integrationTest(char* filename)
{
  
  absorp* buffer[51] = {0};
  
  
  do {
    if(filseState != EOF) {
      myAbsorp = FIR(myAbsorp, buffer);
      x = IIR(x, old_x, myAbsorp);
      mesure();
      affiche();
    }
  } while (fileState != EOF);
  
  
}
