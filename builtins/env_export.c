#include "builtins.h"

int	env_export(char **args)
{
	unsigned int	i;

	if (args[1] == NULL)
		return (declare_x());
	i = 1;
	while (args[i] != NULL)
		if (split_append_env(args[i++]) == 1)
			return (1);
	return (0);
}
