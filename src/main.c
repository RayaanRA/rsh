#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int pid;
	int status;
	int ret = 0;

	int size = 51;
	char input[51];

	while(1) {

		printf("rsh > ");
		fgets(input, size, stdin);
		input[strcspn(input, "\n")] = '\0';
		// parse more
		if (strcmp(input, "exit") == 0) {
			exit(EXIT_SUCCESS);
		}
		pid = fork();

		if (pid == -1) {
			perror("fork");
		} else if (pid == 0) {
			ret = execvp(input, NULL);
			if (ret == -1) {
				printf("Error executing command.\n");
				exit(EXIT_FAILURE);
			}
		} else {
			waitpid(pid, &status, WUNTRACED);
		}

	};
}