#include "env.h"
#include "env_substr.h"

t_env	*split_append_env(char *env)
{
	char	*var;
	char	*val;
	t_env	*new_env;

	var = var_substr(env);
	if (var == NULL)
		return (NULL);
	val = val_substr(env);
	if (val == NULL)
	{
		free(var);
		return (NULL);
	}
	new_env = append_env_list(var, val);
	free(var);
	free(val);
	return (new_env);
}
