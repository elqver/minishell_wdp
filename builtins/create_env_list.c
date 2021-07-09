#include "env.h"

void	create_env_list(char **envp)
{
	unsigned int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		//printf("ENVP = |%s|\n", envp[i]);
		split_append_env(envp[i++]);
	}
	append_env_list("OLDPWD", NULL);
}
