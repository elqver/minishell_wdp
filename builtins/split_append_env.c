#include "env.h"
#include "env_substr.h"

int	split_append_env(char *env)
{
	char	*var;
	char	*val;
	int		ret_status;

	var = var_substr(env);
	if (var == NULL)
		return (1);
	val = val_substr(env);
	ret_status = append_env_list(var, val);
	free(var);
	free(val);
	return (ret_status);
}
