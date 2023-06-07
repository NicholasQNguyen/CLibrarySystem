#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "lib.h"


/*
Parses through a file and returns the name of the book that we're looking for.
@param library the file to go through
@param title the string to find. Expects to be lowercase
@returns the title of the book found
*/
char* findBook(FILE *library, char title[])
{
    char currentTitle[2048];
    char lowerCurrentTitle[2048];
    while(fgets(currentTitle, 2048, library) != NULL)
    {
        // Slight optimization
        // Subtract 1 for the newline character
        if (strlen(title) != strlen(currentTitle) - 1)
        {
            continue;
        }
        // Lowercase the database entry
        for (int i = 0; i < strlen(currentTitle); i++)
        {
            lowerCurrentTitle[i] = tolower(currentTitle[i]);
        }
        // Need the -1 to exclude the newline and get 0 from strncmp
        if (strncmp(title, lowerCurrentTitle, strlen(title) - 1) == 0)
        {
            char *book = currentTitle;
            return book;
        }
    }
    // Return NULL if we go through the whole database and don't find it
    return NULL;
}


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
    // book[strcspn(book, "\n")] = '\0';
    for (int i = 0; i < strlen(book); i++)
    {
        printf("%c \n", book[i]);
    }
    char* newlineLessBook = newlineRemove(book);
    for (int i = 0; i < strlen(book); i++)
    {
        printf("%c \n", newlineLessBook[i]);
    }
    (book) ? printf("%s is available! \n", newlineLessBook) : printf("%s not found. \n", newlineLessBook);

    // Close the file
    if (ptr)
    {
        fclose(ptr);
    }

    return 0;
}
