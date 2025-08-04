#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void handle_cd(char* argv[], ShellContext *ctx);


bool handle_built_in_commands(char* argv[], ShellContext *ctx) {
    if (!argv[0]) return false;

    if (strcmp(argv[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    }

    if (strcmp(argv[0], "cd") == 0) {
        handle_cd(argv, ctx);
        return true;
    }

    if (strcmp(argv[0], "help") == 0) {
        puts("\n--Help menu--\nBuilt-in commands:\nexit - exit the shell\ncd - change working directory\nhelp - see the help menu\n");
        return true;
    }

    return false;
}

int split_into_tokens(char* argv[], char input[], char tokens[][64]) {
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

void handle_cd(char* argv[], ShellContext *ctx) {
    const char *path = argv[1] ? argv[1] : getenv("HOME");
    if (chdir(path) != 0) {
        perror("cd");
    }
    getcwd(ctx->wd, 50);
}

Redirection parse_redirection(char *argv[], int *token_count) {
    Redirection redir_info = { .type = REDIR_NONE, .file = NULL };

    if (*token_count < 3) return redir_info;

    for (int i = 0; argv[i] != NULL; i++) {
        if ((strcmp(argv[i], ">") == 0 || strcmp(argv[i], "<") == 0) && argv[i + 1] != NULL) {
            redir_info.type = (strcmp(argv[i], ">") == 0) ? REDIR_OUTPUT : REDIR_INPUT;
            redir_info.file = argv[i + 1];

            // shift argv to remove redirection
            int j = i;
            while (argv[j + 2] != NULL) {
                argv[j] = argv[j + 2];
                j++;
            }
            argv[j] = NULL;
            *token_count -= 2;
            break;
        }
    }

    return redir_info;
}





