#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lib.h"

bool thereAreCommandLineArgs(int argc)
{
    return (argc != 1);
}


char* argvToOneString(int argc, char* argv[])
{
    int v = 0;
    char* title = (char*)malloc(v);
    for (int i = 1; i < argc; i++)
    {
        v += strlen(argv[i]) + 1;
        title = (char*)realloc(title, v);
        strcat(title, argv[i]);
        // Add spaces unless we're at the end
        if (i != argc - 1)
        {
            strcat(title, " ");
        }
    }
    return title;
}


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
