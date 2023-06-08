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


/*
@return 0 on successful execution
        1 if no command line arguments are provided
        2 if a library is not found 
        3 if the title is not found in the library
        4 if there was an error deleting the original library file
        5 if there was an error renaming the temporary file
*/
int main(int argc, char* argv[])
{
    if (!thereAreCommandLineArgs(argc))
    {
        printf("Command line arguments expected. \n");
        printf("Use the -h flag for help. \n");
        printf("\"./removebook -h\"");
        return 1;
    }
    if (argc == 2 && strncmp("-h", argv[1], strlen(argv[1])) == 0)
    {
        printf("This program removes books from the books.txt file. \n");
        printf("Books must be spelled exactly as they appear in the database, but they are not case sensitive. \n");
        printf("After entering \"./removeBook\", books titles may be entered naturally with spaces. \n");
        printf("Format: \"./removeBook <TITLE OF BOOK>\". \n");
        return 0;
    }

    FILE* ptr;
    if (access("books.txt", F_OK) != 0)
    {
        printf("No library found \n");
        printf("Add a book using addBook.\n");
        return 2;
    }
    else
    {
        ptr = fopen("books.txt", "r+");
    }

    // Concatenate the command line args to 1 string
    char* title = argvToOneString(argc, argv);
    // Lowercase the search query
    char* lowerCaseTitle = strToLowerCase(title);

    int result = removeBook(ptr, lowerCaseTitle);

    // Error handling
    if (result == 1)
    {
        printf("Title not found in library. \n");
        if (ptr)
        {
            fclose(ptr);
        }
        return 3;
    }
    if (result == 2)
    {
        printf("ERROR: Problem in deleting original library file. \n");
        if (ptr)
        {
            fclose(ptr);
        }
        return 4;
    }
    if (result == 3)
    {
        printf("ERROR: Problem in renaming temp.txt to book.txt. \n");
        if (ptr)
        {
            fclose(ptr);
        }
        return 5;
    }

    // Close the original file
    if (ptr)
    {
        fclose(ptr);
    }

    printf("Successfully removed %s! \n", title);
    return 0;
}
