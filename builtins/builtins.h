#ifndef BUILTINS_H
# define BUILTINS_H

# include "../ast/ast.h"
# include "env.h"

void	echo(char **args);
void	cd(char **args);
void	pwd(char **args);
void	env_export(char **args);
void	unset(char **args);
void	env(char **args);
void	wdp_exit(char **args);

#endif
