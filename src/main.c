#include "parse.h"
#include "exec.h"

int main() {

	int size = 1024;
	char input[1024];
	char tokens[64][64];
	char* argv[65];
	char wd[50];
	bool didExecute = false;
	(void) getcwd(wd, 50);

	while(1) {

		printf("(rsh) %s > ", wd);
		fgets(input, size, stdin);
		didExecute = parseInput(input, argv, wd, tokens);
		if (!didExecute) {
			execute(argv);
		}
	};
}