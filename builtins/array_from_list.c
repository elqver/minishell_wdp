#include "env.h"

static size_t	list_len(t_env *env_list)
{
	size_t	i;

	i = 0;
	while (env_list != NULL)
	{
		i++;
		env_list = env_list->next;
	}
	return (i);
}

static char	*strdup_env(t_env *env_node)
{
	char	*env;
	size_t	var_len;
	size_t	val_len;

	var_len = strlen(env_node->var);
	val_len = strlen(env_node->val);
	env = calloc(sizeof(char), var_len + val_len + 2);
	env = strncpy(env, env_node->var, var_len);
	env[var_len] = '=';
	env = strncpy(env + var_len + 1, env_node->val, val_len);
	return (env);
}

void	delete_env_arr(char **env_arr)
{
	unsigned int	i;

	i = 0;
	while (env_arr[i] != NULL)
		free(env_arr[i++]);
	free(env_arr);
}

char	**array_from_list(t_env *env)
{
	char	**env_arr;
	int		i;

	env_arr = calloc(sizeof(char *), list_len(env) + 1);
	i = 0;
	while (env != NULL)
	{
		env_arr[i] = strdup_env(env);
		i++;
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
