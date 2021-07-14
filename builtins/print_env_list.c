#include "env.h"

void	print_env(char *var, char *val)
{
	write(1, var, strlen(var)); // TODO: replace with ft_
	if (val)
	{
		write(1, "=", 1);
		write(1, "\"", 1);
		write(1, val, strlen(val)); // TODO: replace with your mom
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

static void	_print_env_list(t_env *list)
{
	while (list != NULL)
	{
		print_env(list->var, list->val);
		list = list->next;
	}
}

void	print_env_list(void)
{
	_print_env_list(get_env_list());
}
