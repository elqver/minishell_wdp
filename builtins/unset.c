#include "builtins.h"
#include "../utils/utils.h"

static int	check_env_var(char *var)
{
	static t_state	*automaton;

	if (var == NULL)
		return (1);
	if (automaton == NULL)
		automaton = env_automaton();
	return (get_lexeme_len(automaton, var) != ft_strlen(var));
}

static int	unset_one(char *variable)
{
	t_env	*cur;
	t_env	*prev;

	if (check_env_var(variable) == 1)
		return (1);
<<<<<<< HEAD
	cur = *env_list(get);
	if (ft_strcmp(cur->var, variable) == 0)
=======
	cur = get_env_list();
	if (strcmp(cur->var, variable) == 0)
>>>>>>> f4960ae9bbf3e6b6db9c0ed6dede2deeb0034ed3
	{
		cur = cur->next;
		return (delete_env_node(&cur));
	}
	prev = cur;
	cur = cur->next;
	while (cur != NULL)
	{
		if (ft_strcmp(cur->var, variable) == 0)
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
