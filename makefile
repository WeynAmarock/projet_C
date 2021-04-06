projet.exe: main.o iir.o fir.o 
	gcc main.o iir.o fir.o  -o projet.exe 

main.o: main.c define.h
	gcc -g -c main.c

iir.o: iir.c iir.h
	gcc -g -c iir.c

fir.o: fir.c fir.h
	gcc -g -c fir.c


clean:
	rm *.o projet
