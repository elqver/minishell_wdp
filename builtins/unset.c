#include "builtins.h"

static void	unset_one(char *variable)
{
	t_env	**env;
	t_env	*cur;
	t_env	*prev;

	env = env_list(get);
	cur = *env;
	if (strcmp(cur->var, variable) == 0)
	{
		*env = (*env)->next;
		free(cur->var);
		free(cur->val);
		free(cur);
		return ;
	}
	prev = cur;
	cur = cur->next;
	while (cur != NULL)
	{
		if (strcmp(cur->var, variable) == 0)
		{
			prev->next = cur->next;
			free(cur->var);
			free(cur->val);
			free(cur);
			return ;
		}
		cur = cur->next;
		prev = prev->next;
	}
}

void		unset(char **args)
{
	unsigned int	i;

	i = 0;
	while (args[i] != NULL)
		unset_one(args[i++]);
}

