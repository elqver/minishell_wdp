#include "env.h"

t_env	**env_list(t_env **(* action)(t_env **))
{
	static t_env	*env_list;

	return (action(&env_list));
}

t_env	**get(t_env **env_list)
{
	return (env_list);
}
