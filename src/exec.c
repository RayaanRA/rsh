#include "exec.h"
#include "parse.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void execute(char* argv[], Redirection redir_info, PipeInfo pipe_info) {
    if (pipe_info.has_pipe) {
        int fds[2];
        if (pipe(fds) == -1) {
            perror("pipe");
            return;
        }

        pid_t left_pid = fork();
        if (left_pid == -1) {
            perror("fork");
            return;
        }

        if (left_pid == 0) {
            // Left command (write end)
            if (dup2(fds[1], STDOUT_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(fds[0]);
            close(fds[1]);

            if (execvp(pipe_info.left_argv[0], pipe_info.left_argv) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }

        pid_t right_pid = fork();
        if (right_pid == -1) {
            perror("fork");
            return;
        }

        if (right_pid == 0) {
            // Right command (read end)
            if (dup2(fds[0], STDIN_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(fds[0]);
            close(fds[1]);

            if (execvp(pipe_info.right_argv[0], pipe_info.right_argv) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }

        close(fds[0]);
        close(fds[1]);

        int status;
        waitpid(left_pid, &status, 0);
        waitpid(right_pid, &status, 0);

    } else {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return;
        }

        if (pid == 0) {

            if (redir_info.type == REDIR_OUTPUT && redir_info.file) {
                int fd = open(redir_info.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                if (dup2(fd, STDOUT_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(fd);
            } else if (redir_info.type == REDIR_INPUT && redir_info.file) {
                int fd = open(redir_info.file, O_RDONLY);
                if (fd < 0) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                if (dup2(fd, STDIN_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(fd);
            }

            if (execvp(argv[0], argv) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }

        int status;
        waitpid(pid, &status, 0);
    }
}