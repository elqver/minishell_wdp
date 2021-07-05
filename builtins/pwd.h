#ifndef PWD_H
# define PWD_H

# include <unistd.h>
# include <stdlib.h>
# include "../ast.h"

# define PATH_MAX 4096

void	pwd(t_ast *pwd_node, char **envp);

#endif
