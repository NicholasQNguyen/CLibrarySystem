CC = gcc
DEPS = lib.c

addBook:
	$(CC) -o addBook addBook.c $(DEPS) -Wall

findBook:
	$(CC) -o findBook findBook.c $(DEPS) -Wall

removeBook:
	$(CC) -o removeBook removeBook.c findBook.c $(DEPS) -Wall
