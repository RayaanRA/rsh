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

        int token_count = split_into_tokens(argv, input, tokens);
        handle_env_variables(argv, token_count);
        Redirection redir_info = parse_redirection(argv, &token_count);
        PipeInfo pipe_info = handle_pipe(argv);
        if (!handle_built_in_commands(argv, &ctx)) {
            execute(argv, redir_info, pipe_info);
        }

        input[0] = '\0';
    }
}

void sigint_handler(int signum) {
    ctx.sigint_received = 1;
    waitpid(-1, NULL, WNOHANG);
    signal(SIGINT, sigint_handler);
}