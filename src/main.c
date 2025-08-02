#include "parse.h"
#include "exec.h"

char wd[50];
int sigintReceived = 0;
void sigintHandler(int signum);

int main() {

	int size = 1024;
	char input[1024];
	char tokens[64][64];
	char* argv[65];
	bool didExecute = false;
	(void) getcwd(wd, 50);
	if (signal(SIGINT, sigintHandler) == SIG_ERR) {
		perror("signal");
		return EXIT_FAILURE;
	}
	
	while (1) {
    	if (sigintReceived) {
        	putchar('\n');
        	sigintReceived = 0;
    	}

    	printf("(rsh) %s > ", wd);
    	if (!fgets(input, size, stdin)) break; // handle EOF

    	int tokenCount = tokenize(input, argv, tokens);

    	if (!parseInput(input, argv, tokens)) {
        	execute(argv);
    	}
    	input[0] = '\0';
	}

}

void sigintHandler(int signum) {
	sigintReceived = 1;
	waitpid(-1, NULL, WNOHANG);
	signal(SIGINT, sigintHandler);
}