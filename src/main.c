#include "parse.h"
#include "exec.h"

int main() {

	int size = 1024;
	char input[1024];
	char* argv[64];
	char wd[50];
	bool didExecute = false;
	(void) getcwd(wd, 50);

	while(1) {

		printf("(rsh) %s > ", wd);
		fgets(input, size, stdin);
		didExecute = parseInput(input, argv, wd);
		if (!didExecute) {
			execute(argv);
		}
	};
}