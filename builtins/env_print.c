#include "builtins.h"

int	env(char **args)
{
	(void)args;
	print_env_list();
	return (0);
}
