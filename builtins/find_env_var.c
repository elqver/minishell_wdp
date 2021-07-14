#include "env.h"

t_env	*find_env_var(char const *name)
{
	t_env	*env;

	env = get_env_list();
	while (env != NULL)
	{
		if (strcmp(env->var, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
