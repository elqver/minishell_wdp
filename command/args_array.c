#include "command_commands.h"
#include "../builtins/builtins.h"

int	delete_args_arr(char **args)
{
	unsigned int	i;

	i = 0;
	while (args[i] != NULL)
		free(args[i++]);
	free(args);
	return (0);
}

static int	calculate_args_arr_length(t_ast *self)
{
	int	length;

	length = 0;
	while (self != NULL)
	{
		length++;
		self = self->right;
	}
	return (length);
}

char	**generate_args_arr(t_ast *self)
{
	char	**argv;
	int		argc;
	int		i;

	argc = calculate_args_arr_length(self);
	argv = ft_calloc(sizeof(char *), argc + 1);
	i = 0;
	while (i < argc)
	{
		argv[i] = strdup(self->data);
		self = self->right;
		i++;
	}
	return (argv);
}
