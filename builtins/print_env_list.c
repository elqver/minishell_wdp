#include "env.h"
#include "../utils/utils.h"

void	print_env(char *var, char *val)
{
	write(1, var, ft_strlen(var)); 
	if (val)
	{
		write(1, "=", 1);
		write(1, "\"", 1);
		write(1, val, ft_strlen(val)); 
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
