//#include "pwd.h"
#include "builtins.h"
#include <limits.h>

void	pwd(char **args)
{
	char	*cwd;

	(void)args;
	cwd = NULL;
	cwd = getcwd(cwd, PATH_MAX);
	write(1, cwd, strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
}
