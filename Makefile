all: test-lab

test-lab: labyrinthe.o test.c
	gcc -Wall  -g -o test-lab labyrinthe.o test.c

labyrinthe.o: labyrinthe.c
	gcc -c -Wall -g -o labyrinthe.o labyrinthe.c

clean :
	rm labyrinthe.o test-lab 
