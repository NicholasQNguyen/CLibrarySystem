#ifndef _LIBH_
#define _LIBH_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool thereAreCommandLineArgs(int argc);

char** strToLowerCase(int numberOfWords, char* phrase[]);

char* argvToOneString(int argc, char* argv[]);

char* findBook(FILE* library, char title[]);
#endif
