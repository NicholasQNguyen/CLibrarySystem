#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "lib.c"


void addBook(FILE *library, char *title)
{
    fprintf(library, "%s\n", title);
}

int main(int argc, char* argv[])
{
    if (!thereAreCommandLineArgs(argc))
    {
        printf("Command line arguments expected. \n");
        printf("format: \"./addBook <TITLE OF BOOK>\". \n");
        return 1;
    }
    FILE *ptr;
    // Create "books.txt" if it doesn't exist elsewise append to it
    ptr = (access("books.txt", F_OK) != 0) ? fopen("books.txt", "w") : fopen("books.txt", "a");
    // Concatenate the command line args to 1 string
    int v = 0;
    char *title = (char *)malloc(v);
    for (int i = 1; i < argc; i++)
    {
        v += strlen(argv[i]) + 1;
        title = (char *)realloc(title, v);
        strcat(title, argv[i]);
        strcat(title, " ");
    }

    addBook(ptr, title);

    if (ptr)
    {
        fclose(ptr);
    }

    return 0;
}
