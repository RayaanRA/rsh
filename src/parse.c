#include "parse.h"

bool parseInput(char input[], char* argv[], char wd[]) {
	input[strcspn(input, "\n")] = '\0';

	char *token = strtok(input, " \t\n");
	int i = 0;
	while (token && i < 64) {
		argv[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	if (i > 0) {
		argv[i] = NULL;
	}
	if (strcmp(argv[0], "exit") == 0) {
		exit(EXIT_SUCCESS);
	} else if (strcmp(argv[0], "cd") == 0) {
		if (i == 1) {
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


