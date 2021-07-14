#ifndef BUILTINS_H
# define BUILTINS_H

# include "../ast/ast.h"
# include "../parser/automata/nfa.h"
# include "env.h"

int		echo(char **args);
int		cd(char **args);
int		pwd(char **args);
int		env_export(char **args);
int		unset(char **args);
int		env(char **args);
int		wdp_exit(char **args);

int		set_exit_code(int new_code);
int		get_exit_code(void);
void	waitpid_logging(pid_t pid);

#endif
