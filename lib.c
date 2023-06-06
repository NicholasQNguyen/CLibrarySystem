#include <stdbool.h>
#include <string.h>

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
