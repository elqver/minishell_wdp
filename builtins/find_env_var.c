#include "env.h"
#include "../utils/utils.h"

t_env	*find_env_var(char *name)
{
	t_env	*env;

	env = get_env_list();
	while (env != NULL)
	{
		if (ft_strcmp(env->var, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

