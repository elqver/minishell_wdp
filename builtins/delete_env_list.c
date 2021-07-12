#include "env.h"

static void	_delete_env_list(t_env **list)
{
	t_env	*t;

	while (*list != NULL)
	{
		t = (*list)->next;
		delete_env_node(list);
		*list = t;
	}
}

void	delete_env_list(void)
{
	_delete_env_list(env_list(get));
}

