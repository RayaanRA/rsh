#include "exec.h"
#include "parse.h"

void execute(char* argv[], Redirection redir_info) {
    int pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }
    if (pid == 0) {
        if (redir_info.type == REDIR_OUTPUT && redir_info.file) {
            int fd = open(redir_info.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) { perror("open"); exit(1); }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } else if (redir_info.type == REDIR_INPUT && redir_info.file) {
            int fd = open(redir_info.file, O_RDONLY);
            if (fd < 0) { perror("open"); exit(1); }
            dup2(fd, STDIN_FILENO);
            close(fd);            
        }

        if(execvp(argv[0], argv) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(pid, NULL, 0);
    }
}


