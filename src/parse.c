#include "parse.h"

bool parseInput(char input[], char* argv[], char wd[], char tokens[][64]) {
	input[strcspn(input, "\n")] = '\0';

	/*char *token = strtok(input, " \t\n");
	int i = 0;
	while (token && i < 64) {
		argv[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	if (i > 0) {
		argv[i] = NULL;
	}

	*/

	tokenize(input, argv, tokens);

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

void tokenize(char input[], char* argv[], char tokens[][64]) {
	int i = 0;
	int j = 0;
	int h = 0;
	while (input[i] != '\0' && h < 64) {
		while (input[i] != ' ' && input[i] != '\0') {
			if (input[i] != '"') {
				tokens[h][j] = input[i];
				j++;
				i++;
			} else {
				i++; // skip first quote
				while (input[i] != '"') {
					tokens[h][j] = input[i];
					j++;
					i++;
				}
				i++; // skip last quote
			}

		}
		tokens[h][j] = '\0';
		i++;
		h++;
		j = 0;
	}

	for (int k = 0; k < h; k++) {
		argv[k] = tokens[k];
	}
	if (h > 0) {
		argv[h] = NULL;
	}
}


