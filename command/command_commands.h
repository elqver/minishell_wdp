# ifndef COMMAND_COMMANDS_H
# define COMMAND_COMMANDS_H

# include "../ast/ast.h"
# include "../builtins/builtins.h"
# include "../builtins/env.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/wait.h>

# define ONE_LEFT_REDIR		0
# define ONE_RIGHT_REDIR	1
# define TWO_LEFT_REDIR		2
# define TWO_RIGHT_REDIR	3

//		AST nodes creation
t_ast	*create_command_node(t_token *token);
t_ast	*create_pipe_node(void);
t_ast	*create_redir_node(t_token *token);
//		Strings array from AST branch
char	**generate_args_arr(t_ast *self);
int		delete_args_arr(char **args);
//		Main command execution interface
int		execute_command(t_ast *self);
//		PATH commands execution
int		execute_command_from_path(char **av);
//		Binary file execution
int		execute_binary_file(char *path, char **av);
int		contains_slash(char *path_to_binary);
//		Pipe handling
int		pipe_exec(t_ast *self);
//		Redir handling
int		redir_exec(t_ast *self);

#endif
