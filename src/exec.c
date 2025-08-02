#include "exec.h"

void execute(char* argv[]) {
    int pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }
    if (pid == 0) {
        // child: parse argv for redirection tokens:
        for (int i = 0; argv[i] != NULL; i++) {
            if (strcmp(argv[i], ">") == 0) {
                int fd = open(argv[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
                // remove redirection tokens from argv
                while (argv[i + 2] != NULL) {
                    argv[i] = argv[i + 2];
                    i++;
                }
                argv[i] = NULL;
                break;
            }
        }
        execvp(argv[0], argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid, NULL, 0);
    }
}


