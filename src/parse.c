#include "parse.h"
#include "parse.h"
#include <stdlib.h>  // exit, getenv
#include <stdio.h>   // printf, perror
#include <unistd.h>  // chdir, getcwd
#include <string.h>  // strcmp

void handle_env_variables(char* argv[], int token_count);


bool parse_input(ShellContext *ctx, char input[], char* argv[], char tokens[][64]) {
    if (strcmp(argv[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    } else if (strcmp(argv[0], "cd") == 0) {
        if (!argv[1]) {
            if (chdir(getenv("HOME")) != 0) {
                perror("cd");
            }
        } else {
            if (chdir(argv[1]) != 0) {
                perror("cd");
            }
        }

        (void) getcwd(ctx->wd, 50);
        return true;
    } else if (strcmp(argv[0], "help") == 0) {
        printf("\n--Help menu--\nBuilt-in commands:\nexit - exit the shell\ncd - change working directory\nhelp - see the help menu\n\n");
        return true;
    }

    return false;
}

int tokenize(char input[], char* argv[], char tokens[][64]) {
	input[strcspn(input, "\n")] = '\0';
	int input_index = 0;
	int token_index = 0;
	int token_count = 0;

	while (input[input_index] != '\0' && token_count < 64) {
		while (input[input_index] == ' ') input_index++; // skip leading spaces

		while (input[input_index] != ' ' && input[input_index] != '\0') {
			if (input[input_index] != '"') {
				tokens[token_count][token_index++] = input[input_index++];
			} else {
				input_index++; // skip opening quote
				while (input[input_index] != '"' && input[input_index] != '\0') {
					tokens[token_count][token_index++] = input[input_index++];
				}
				if (input[input_index] == '"') input_index++; // skip closing quote
			}
		}

		tokens[token_count][token_index] = '\0';
		token_index = 0;
		token_count++;
		if (input[input_index] != '\0') input_index++; // skip space
	}

	for (int j = 0; j < token_count; j++) {
		argv[j] = tokens[j];
	}

	handle_env_variables(argv, token_count);

	if (token_count > 0) {
		argv[token_count] = NULL;
	}

	return token_count;
}

void handle_env_variables(char* argv[], int token_count) {
	for (int i = 0; i < token_count; i++) {
		if (argv[i][0] == '$') {
			char *env = getenv(argv[i] + 1);
			if (env) {
				argv[i] = env;
			} else {
				argv[i] = "";
			}
		}
	}
}
