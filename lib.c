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


char* strToLowerCase(char phrase[])
{
    char* returnedString = (char*)malloc((strlen(phrase) + 1) * sizeof(char));
    for (int i = 0; i < strlen(phrase); i++)
    {
        // phrase[i] = tolower(phrase[i]);
        returnedString[i] = tolower(phrase[i]);
    }
    // return phrase;
    return returnedString;
}
