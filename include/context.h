#ifndef __CONTEXT__
#define __CONTEXT__

typedef struct {
    char wd[50];
    int sigint_received;
} ShellContext;

typedef enum { REDIR_NONE, REDIR_OUTPUT, REDIR_INPUT } RedirType;

typedef struct {
    RedirType type;
    char *file;
} Redirection;

typedef struct {
    char** left_argv;
    char** right_argv;
    bool has_pipe;
} PipeInfo;

#endif
