#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "lib.h"


/*
Parses through a file and returns the line number that the title appears in.
@param library the file to go through
@param title the string to find. Expects to be lowercase
@return The line number of the title or -1 if it is not found.
*/
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


/*
Parses through a file and removes the line where the title appears.
@param library the file to go through
@param title the string to find
@return 0 on a successful removal or 1 if it is not found
*/
int removeBook(FILE* library, char* title)
{
    int lineNumber = findLineNumber(library, title);
    if (lineNumber == -1)
    {
        return 1;
    }
    return 0;
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

    int result = removeBook(ptr, title);

    if (result != 0)
    {
        printf("Title not found in library. \n");
        if (ptr)
        {
            fclose(ptr);
        }
        return 1;
    }
    if (ptr)
    {
        fclose(ptr);
    }

    return 0;
}
