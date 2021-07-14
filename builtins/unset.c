#include "builtins.h"

static int	check_env_var(char *var)
{
	static t_state	*automaton;

	if (var == NULL)
		return (1);
	if (automaton == NULL)
		automaton = env_automaton();
	return (get_lexeme_len(automaton, var) != strlen(var)); // TODO: ft_
}

static int	unset_one(char *variable)
{
	t_env	*cur;
	t_env	*prev;

	if (check_env_var(variable) == 1)
		return (1);
	cur = get_env_list();
	if (strcmp(cur->var, variable) == 0)
	{
		cur = cur->next;
		return (delete_env_node(&cur));
	}
	prev = cur;
	cur = cur->next;
	while (cur != NULL)
	{
		if (strcmp(cur->var, variable) == 0)
		{
			prev->next = cur->next;
			return (delete_env_node(&cur));
		}
		cur = cur->next;
		prev = prev->next;
	}
	return (0);
}

int	unset(char **args)
{
	unsigned int	i;
	int				ret_status;

	i = 0;
	ret_status = 0;
	while (args[i] != NULL)
		ret_status |= unset_one(args[i++]);
	return (ret_status);
}
