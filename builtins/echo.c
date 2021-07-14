#include "builtins.h"
#include "../utils/utils.h"

int	echo(char **args)
{
	unsigned int	i;
	int				newline_flag;

	if (args[1] == NULL)
		return (!!write(1, "\n", 1));
	newline_flag = 1;
	i = 1;
	if (ft_strcmp(args[1], "-n") == 0)
	{
		newline_flag = 0;
		i = 2;
	}
	while (args[i] != NULL)
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (newline_flag)
		write(1, "\n", 1);
	return (0);
}
