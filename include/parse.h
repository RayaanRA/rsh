#ifndef __PARSE__
#define __PARSE__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

bool parseInput(char input[], char* argv[], char wd[], char tokens[][64]);
void tokenize(char input[], char* argv[], char tokens[][64]);

#endif

