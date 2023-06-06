#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "lib.h"


int main(int argc, char* argv[])
{
    if (!thereAreCommandLineArgs(argc))
    {
        printf("Command line arguments expected. \n");
        printf("format: \"./findBook <TITLE OF BOOK>\". \n");
        return 1;
    }

    FILE *ptr;
    if (access("books.txt", F_OK) != 0)
    {
        printf("No library found \n");
        printf("Add a book using addBook.\n");
        return 1;
    }
    else
    {
        ptr = fopen("books.txt", "r");
    }

    // Concatenate the command line args to 1 string
    char* title = argvToOneString(argc, argv);
    // Convert the title into lowercase for searching
    title = strToLowerCase(title);

    char* book = findBook(ptr, title);

    // Replace the newline from the file to a null terminator
    book[strcspn(book, "\n")] = '\0';
    (book) ? printf("%s is available! \n", book) : printf("Not found. \n");

    // Close the file
    if (ptr)
    {
        fclose(ptr);
    }

    return 0;
}
