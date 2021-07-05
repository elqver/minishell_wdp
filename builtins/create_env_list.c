#include "env.h"

/*
static void	_create_env_list(t_env **list, char **envp)
{
	unsigned int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		split_append_env(list, envp[i]);
		i++;
	}
}

void	create_env_list(char **envp)
{
	_create_env_list(env_list(get), envp);
}

*/

void	create_env_list(char **envp)
{
	unsigned int	i;

	i = 0;
	while (envp[i] != NULL)
		split_append_env(envp[i++]);
}
