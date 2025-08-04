#ifndef __EXEC__
#define __EXEC__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "context.h"


void execute(char* argv[], Redirection redir_info, PipeInfo pipe_info);



#endif