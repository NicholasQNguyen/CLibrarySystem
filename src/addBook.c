#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "lib.h"


/*
Write the title into a file. Adds a newline at the end so each book is on an individual line.
@param library the file to go through
@param title the string to find
@return true if successfully added or false if not
*/
int addBook(FILE* library, char* title)
{
    return fprintf(library, "%s\n", title) > 0;
}


/*
@return 0 on successful execution
        1 if no command line arguments are provided
        2 if there was an error adding to the file
*/
int main(int argc, char* argv[])
{
    if (!thereAreCommandLineArgs(argc))
    {
        printf("Command line arguments expected. \n");
        printf("Use the -h flag for help. \n");
        printf("\"./addbook -h\"");
        return 1;
    }
    if (argc == 2 && strncmp("-h", argv[1], strlen(argv[1])) == 0)
    {
        printf("This program adds books to the books.txt file. \n");
        printf("Books are entered exactly as they are spelled. \n");
        printf("After entering \"./addbook\", books titles may be entered naturally with spaces. \n");
        printf("format: \"./addBook <TITLE OF BOOK>\". \n");
        return 0;
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
        return 2;
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
