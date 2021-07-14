#include "builtins.h"
#include <limits.h>

int	pwd(char **args)
{
	char	*cwd;

	(void)args;
	cwd = NULL;
	cwd = getcwd(cwd, PATH_MAX);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
	return (0);
}
