#include "pwd.h"

void	pwd(t_ast *pwd_node, char **envp)
{
	char	*cwd;

	(void)pwd_node;
	cwd = NULL;
	cwd = getcwd(cwd, PATH_MAX);
	write(1, cwd, strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
}
