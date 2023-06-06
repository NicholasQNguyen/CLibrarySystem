#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lib.h"


/*
Write the title into a file. Adds a newline at the end so each book is on an individual line.
@param library the file to go through
@param title the string to find
*/
int addBook(FILE* library, char *title)
{
    return fprintf(library, "%s\n", title) > 0;
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
    char* title = argvToOneString(argc, argv);

    if (addBook(ptr, title) < 0)
    {
        printf("ERROR adding to file. \n");
        if (ptr)
        {
            fclose(ptr);
        }
        return 1;
    }
    else
    {
        printf("%s added successfully! \n", title);
    }

    if (ptr)
    {
        fclose(ptr);
    }

    return 0;
}
