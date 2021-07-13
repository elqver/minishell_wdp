# ifndef COMMAND_COMMANDS_H
# define COMMAND_COMMANDS_H

# include "../ast/ast.h"
# include "../builtins/builtins.h"
# include "../builtins/env.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "../utils/ft_string.h"
# include <dirent.h>
# include <sys/wait.h>
#include <string.h> // TODO: delete

# define ONE_LEFT_REDIR		1
# define ONE_RIGHT_REDIR	2
# define TWO_RIGHT_REDIR	3
# define TWO_LEFT_REDIR		4

t_ast	*create_command_node(t_token *token);
t_ast	*create_pipe_node(void);
t_ast	*create_redir_node(t_token *token);

#endif
