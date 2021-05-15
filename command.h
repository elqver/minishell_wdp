#ifndef COMMAND_H
# define COMMAND_H 

#include "ast.h"
#include <string.h> //remove it later
#include <fcntl.h>

int		exec_command(t_ast *command);

#endif
