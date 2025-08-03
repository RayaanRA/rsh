#ifndef __CONTEXT__
#define __CONTEXT__

typedef struct {
    char wd[50];
    int sigint_received;
} ShellContext;

#endif
