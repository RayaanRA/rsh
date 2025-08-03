#include "parse.h"
#include "exec.h"

void sigint_handler(int signum);

ShellContext ctx;

int main() {
    int size = 1024;
    char input[1024];
    char tokens[64][64];
    char* argv[65];

    (void) getcwd(ctx.wd, 50);
    ctx.sigint_received = 0;

    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        return EXIT_FAILURE;
    }

    while (1) {
        if (ctx.sigint_received) {
            putchar('\n');
            ctx.sigint_received = 0;
        }

        printf("(rsh) %s > ", ctx.wd);
        if (!fgets(input, size, stdin)) break;

        int token_count = tokenize(input, argv, tokens);

        if (!parse_input(&ctx, input, argv, tokens)) {
            execute(argv);
        }

        input[0] = '\0';
    }
}

void sigint_handler(int signum) {
    ctx.sigint_received = 1;
    waitpid(-1, NULL, WNOHANG);
    signal(SIGINT, sigint_handler);
}
