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


/*
@return 0 on successful execution
        1 if no command line arguments are provided
        2 if a library is not found 
*/
int main(int argc, char* argv[])
{
    if (!thereAreCommandLineArgs(argc))
    {
        printf("Command line arguments expected. \n");
        printf("Use the -h flag for help. \n");
        printf("\"./findbook -h\"");
        return 1;
    }

    if (argc == 2 && strncmp("-h", argv[1], strlen(argv[1])) == 0)
    {
        printf("This program finds and prints if titles in in the books.txt file. \n");
        printf("Books must be spelled exactly as they appear in the database, but they are not case sensitive. \n");
        printf("After entering \"./findBook\", books titles may be entered naturally with spaces. \n");
        printf("format: \"./findBook <TITLE OF BOOK>\". \n");
        return 0;
    }

    FILE *ptr;
    if (access("books.txt", F_OK) != 0)
    {
        printf("No library found \n");
        printf("Add a book using addBook.\n");
        return 2;
    }
    else
    {
        ptr = fopen("books.txt", "r");
    }

    // Concatenate the command line args to 1 string
    char* title = argvToOneString(argc, argv);
    // Convert the title into lowercase for searching
    char* lowerCaseTitle = strToLowerCase(title);

    char* book = findBook(ptr, lowerCaseTitle);

    if (book)
    {
        char* newlineLessBook = newlineRemove(book);
        printf("%s is available! \n", newlineLessBook);
    }
    else
    {
        printf("%s not found. \n", title);
    }

    // Close the file
    if (ptr)
    {
        fclose(ptr);
    }

    return 0;
}
