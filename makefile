projet.exe: main.o iir.o fir.o fichiers.o affichage.o mesure.o
	gcc main.o iir.o fir.o fichiers.o affichage.o mesure.o -o projet.exe 

main.o: main.c define.h
	gcc -g -c main.c

iir.o: iir.c iir.h
	gcc -g -c iir.c

fir.o: fir.c fir.h
	gcc -g -c fir.c

fichiers.o: fichiers.c fichiers.h
	gcc -g -c fichiers.c

affichage.o: affichage.c affichage.h
	gcc -g -c affichage.c

mesure.o: mesure.c mesure.h
	gcc -g -c mesure.c

clean:
	rm *.o mesure affichage fir fichiers iir main projet
