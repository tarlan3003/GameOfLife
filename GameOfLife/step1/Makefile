CC = gcc

all: clean game

game: main.o drawer.o game.o
	$(CC) main.o drawer.o game.o -o game

main.o: main.c
	$(CC) -c main.c 

drawer.o: drawer.c drawer.h game.h
	$(CC) -c drawer.c

game.o: game.c game.h
	$(CC) -c game.c


clean: 
	rm game *.o

compress:
	@tar -Jcvf step1.tar.xz Makefile README.md *.c *.h

tarclean:
	@rm -r *.tar.xz


