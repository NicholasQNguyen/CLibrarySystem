#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "lib.h"

int findLineNumber(FILE* library, char* title)
{
    char currentTitle[2048];
    char lowerCurrentTitle[2048];
    int currentLine = 0;
    // Find the line number of the 
    while(fgets(currentTitle, 2048, library) != NULL)
    {
        // Slight optimization
        // Subtract 1 for the newline character
        if (strlen(title) != strlen(currentTitle) - 1)
        {
            currentLine++;
            continue;
        }
        // Lowercase the database entry
        strcpy(lowerCurrentTitle, strToLowerCase(currentTitle));
        // Need the -1 to exclude the newline and get 0 from strncmp
        if (strncmp(title, lowerCurrentTitle, strlen(title) - 1) == 0)
        {
            return currentLine;
        }
    }
    return -1;
}


void removeBook(FILE* library, char* title)
{
    int lineNumber = findLineNumber(library, title);
    if (lineNumber == -1)
    {
        return;
    }
}


int main(int argc, char* argv[])
{
    if (!thereAreCommandLineArgs(argc))
    {
        printf("Command line arguments expected. \n");
        printf("format: \"./removeBook <TITLE OF BOOK>\". \n");
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
        ptr = fopen("books.txt", "r+");
    }

    // Concatenate the command line args to 1 string
    char* title = argvToOneString(argc, argv);
    // Lowercase the search query
    title = strToLowerCase(title);

    removeBook(ptr, title);
}
