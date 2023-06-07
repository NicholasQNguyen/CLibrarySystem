#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "lib.h"


/*
Parses through a file and removes the line where the title appears.
@param library the file to go through
@param title the string to find
@return 0 on a successful removal or 1 if it is not found
*/
int removeBook(FILE* library, char* title)
{
    char currentTitle[2048];
    char lowerCurrentTitle[2048];
    // Create a temporary file
    FILE* tempFile = fopen("temp.txt", "w");
    // Copy each line from the original library to a second file
    while(fgets(currentTitle, 2048, library) != NULL)
    {
        // Slight optimization
        // Subtract 1 for the newline character
        if (strlen(title) != strlen(currentTitle) - 1)
        {
            fprintf(tempFile, "%s", currentTitle);
            continue;
        }
        // Lowercase the database entry
        strcpy(lowerCurrentTitle, strToLowerCase(currentTitle));
        // Need the -1 to exclude the newline and get 0 from strncmp
        if (strncmp(title, lowerCurrentTitle, strlen(title) - 1) == 0)
        {
            continue;
        }
        fprintf(tempFile, "%s", currentTitle);
    }
    // Delete the original file
    // If statement for error checking
    if (remove("books.txt") != 0)
    {
        if (tempFile)
        {
            fclose(tempFile);
        }
        return 2;
    }
    if (rename("temp.txt", "books.txt") != 0)
    {
        if (tempFile)
        {
            fclose(tempFile);
        }
        return 3;
    }
    if (tempFile)
    {
        fclose(tempFile);
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

    FILE* ptr;
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

    // Error handling
    if (result == 1)
    {
        printf("Title not found in library. \n");
        if (ptr)
        {
            fclose(ptr);
        }
        return 1;
    }
    if (result == 2)
    {
        printf("ERROR: Problem in deleting original library file. \n");
        if (ptr)
        {
            fclose(ptr);
        }
        return 1;
    }
    if (result == 3)
    {
        printf("ERROR: Problem in renaming temp.txt to book.txt. \n");
        if (ptr)
        {
            fclose(ptr);
        }
        return 1;
    }

    // Close the original file
    if (ptr)
    {
        fclose(ptr);
    }

    return 0;
}
