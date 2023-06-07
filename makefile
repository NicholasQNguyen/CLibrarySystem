CC = gcc
FLAGS = -Wall -Werror
DEPS = lib.o

all:
	make addBook
	make findBook
	make removeBook
	make oClean
	cp stable.txt books.txt

addBook: addBook.o lib.o
	$(CC) -o addBook addBook.o $(DEPS) $(FLAGS)

findBook: findBook.o lib.o
	$(CC) -o findBook findBook.o $(DEPS) $(FLAGS)

removeBook: removeBook.o lib.o
	$(CC) -o removeBook removeBook.o $(DEPS) $(FLAGS)

clean:
	rm addBook
	rm findBook
	rm removeBook

oClean:
	rm *.o
