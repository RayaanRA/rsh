#include "parse.h"
#include "exec.h"

bool parseInput(char input[], char* argv[], char tokens[][64]) {
	// Built-in commands

	if (strcmp(argv[0], "exit") == 0) {
		exit(EXIT_SUCCESS);
	} else if (strcmp(argv[0], "cd") == 0) {
		if (!argv[1]) {
			if (chdir(getenv("HOME")) != 0) {
				perror("cd");
			}
		} else {
			if(chdir(argv[1]) != 0) {
				perror("cd");
			}
		}

		(void) getcwd(wd, 50);
		return true;
	} else if (strcmp(argv[0], "help") == 0) {
		printf("\n--Help menu--\nBuilt-in commands:\nexit - exit the shell\ncd - change working directory\nhelp - see the help menu\n\n");
		return true;
	}

	return false;
}

int tokenize(char input[], char* argv[], char tokens[][64]) {
	input[strcspn(input, "\n")] = '\0';
	int inputIndex = 0;
	int tokenIndex = 0;
	int tokenCount = 0;
	while (input[inputIndex] != '\0' && tokenCount < 64) {
		while (input[inputIndex] != ' ' && input[inputIndex] != '\0') {
			if (input[inputIndex] != '"') {
				tokens[tokenCount][tokenIndex] = input[inputIndex];
				tokenIndex++;
				inputIndex++;
			} else {
				inputIndex++; // skip first quote
				while (input[inputIndex] != '"') {
					tokens[tokenCount][tokenIndex] = input[inputIndex];
					tokenIndex++;
					inputIndex++;
				}
				inputIndex++; // skip last quote
			}

			if (input[inputIndex] == '$') {

			}

		}
		tokens[tokenCount][tokenIndex] = '\0';
		inputIndex++;
		tokenCount++;
		tokenIndex = 0;
	}
	

	for (int j = 0; j < tokenCount; j++) {
		argv[j] = tokens[j];
	}


	for (int i = 0; i < tokenCount; i++) {
		if (argv[i][0] == '$') {
			argv[i] = getenv(argv[i] + 1);
		}
	}

	if (tokenCount > 0) {
		argv[tokenCount] = NULL;
	}
	return tokenCount;
}


void redirect(char *argv[], int *tokenCount) {
	for (int i = 0; i < *tokenCount - 1; i++) {
		if (strcmp(argv[i], ">") == 0) {
			char *file = argv[i + 1];
			int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0) {
				perror("open");
				exit(1);
			}
			if (dup2(fd, 1) < 0) {
				perror("dup2");
				exit(1);
			}
			close(fd);
			for (int j = i; j + 2 < *tokenCount; j++) {
				argv[j] = argv[j + 2];
			}
			argv[*tokenCount - 2] = NULL;
			argv[*tokenCount - 1] = NULL;
			*tokenCount -= 2;
			break;
		}
	}
}


