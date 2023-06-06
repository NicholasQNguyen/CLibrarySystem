#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "lib.c"


void addBook(FILE *library, int wordsInTitle, char* title[])
{
    // Loop in case book title has spaces
    for (int i = 1; i < wordsInTitle; i++)
    {
        // Ensure that we don't have a space at the end
        (i != wordsInTitle - 1) ? fprintf(library, "%s ", title[i]) : fprintf(library, "%s", title[i]);
        /*
        if (i != wordsInTitle - 1)
        {
            fprintf(library, "%s ", title[i]);
        }
        else
        {
            fprintf(library, "%s", title[i]);
        }
        */
    }
    // Add a line between each entry
    fprintf(library, "\n");
}

int main(int argc, char* argv[])
{
    if (!checkForCommandLineArgs(argc))
    {
        printf("Command line arguments expected. \n");
        printf("format: \"./main <TITLE OF BOOK>\". \n");
        return 1;
    }

    FILE *ptr;
    // Create "books.txt" if it doesn't exist elsewise append to it
    ptr = (access("books.txt", F_OK) != 0) ? fopen("books.txt", "w") : fopen("books.txt", "a");
    addBook(ptr, argc, argv);
    if (ptr)
    {
        fclose(ptr);
    }
    return 0;
}
