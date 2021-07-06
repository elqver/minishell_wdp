#include "builtins.h"

void	env_export(char **args)
{
	unsigned int	i;

	if (args[1] == NULL)
	{
		declare_x();
		return ;
	}
	i = 1;
	while (args[i] != NULL)
		split_append_env(args[i++]);
}
