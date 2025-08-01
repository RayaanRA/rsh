#include "exec.h"

void execute(char* argv[]) {
	int pid;
	int ret;
	int status;
	pid = fork();

	if (pid == -1) {
		perror("fork");
	} else if (pid == 0) {

		ret = execvp(argv[0], argv);
		if (ret == -1) {
			printf("Error executing command.\n");
			exit(EXIT_FAILURE);
		}

	} else {
		waitpid(pid, &status, WUNTRACED);
	}
}