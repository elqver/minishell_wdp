#include "env.h"

static t_env	*_append_env_list(t_env **list, char *var, char *val)
{
	if (*list == NULL)
		return (*list = new_env_node(var, val));
	return (_append_env_list(&((*list)->next), var, val));
}

t_env	*append_env_list(char *var, char *val)
{
	return (_append_env_list(env_list(get), var, val));
}

