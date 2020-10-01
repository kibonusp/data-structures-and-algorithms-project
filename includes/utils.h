#ifndef _UTILITIES_H
#define _UTILITIES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *readLine(FILE *stream);
char* strPart(char* str, const void* init, const void* end);
char* strAppend(char* str, char* add);

#endif