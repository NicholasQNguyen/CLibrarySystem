#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "lib.c"


char* findBook(FILE *library, char title[])
{
    char currentTitle[2048];
    char lowerCurrentTitle[2048];
    while(fgets(currentTitle, 2048, library) != NULL)
    {
        // Slight optimization
        if (strlen(title) != strlen(currentTitle))
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
    if (!checkForCommandLineArgs(argc))
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

    // Convert the input into lowercase for searching
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < strlen(argv[i]); j++)
        {
            argv[i][j] = tolower(argv[i][j]);
        }
    }
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
