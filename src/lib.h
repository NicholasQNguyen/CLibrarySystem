#ifndef _LIBH_
#define _LIBH_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/*
Function that will return true or false based on if argc > 1.
@param argc an integer. Typically the argc  or number of arguments.
@return a bool: true if argc > 1, false otherwise
*/
bool thereAreCommandLineArgs(int argc);

/*
Converts an array of char from it's original form to a fully lowercase form.
@param phrase the array of char
@return a char* which is the phrase completely lower case
*/
char* strToLowerCase(char phrase[]);

/*
Converts an array of char* into a single char*.
Takes in argv typically but any char* array would work.
@param argc the number of char* in the array
@param argv the array of char* itself
@return A single char* which is the concatenation of each char* in argv
*/
char* argvToOneString(int argc, char* argv[]);

/*
Strips the newline off of the end of an array of char
@param phrase the array of char. Expects a \n at the end or it'll just 
strip off the last character.
@return the phrase without the newline at the end.
*/
char* newlineRemove(char phrase[]);

#endif
