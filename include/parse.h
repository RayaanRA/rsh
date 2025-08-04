#ifndef __PARSE__
#define __PARSE__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "context.h"

bool handle_built_in_commands(char* argv[], ShellContext *ctx);
int tokenize(char input[], char* argv[], char tokens[][64]);
void redirect(char* argv[], int* token_count);
int split_into_tokens(char* argv[], char input[], char tokens[][64]);
void handle_env_variables(char* argv[], int token_count);
Redirection parse_redirection(char *argv[], int *token_count);
PipeInfo handle_pipe(char* argv[]);
#endif
