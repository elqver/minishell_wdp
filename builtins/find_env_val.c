#include "env.h"

char	*find_env_val(char const *name)
{
	t_env	*env;

	env = find_env_var(name);
	if (env)
		return (env->val);
	return (NULL);
}
