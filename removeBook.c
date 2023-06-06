#include <stdio.h>
#include "lib.c"
#include "findBook.c"


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
    argvToOneString(argc, argv);
}
