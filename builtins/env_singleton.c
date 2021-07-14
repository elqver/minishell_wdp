#include "env.h"

static t_env	**env_singleton(t_env *new_ptr)
{
	static t_env	*saved_ptr;

	if (new_ptr != NULL)
		saved_ptr = new_ptr;
	return (&saved_ptr);
}

t_env	*get_env_list(void)
{
	return (*env_singleton(NULL));
}

t_env	**get_env_list_addr(void)
{
	return (env_singleton(NULL));
}
