#ifndef __PARSE__
#define __PARSE__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

bool parseInput(char input[], char* argv[], char tokens[][64]);
int tokenize(char input[], char* argv[], char tokens[][64]);
void redirect(char* argv[], int* tokenCount);

#endif

