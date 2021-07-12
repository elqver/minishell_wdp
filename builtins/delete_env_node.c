#include "env.h"

int	delete_env_node(t_env **node)
{
	if (*node == NULL)
		return (1);
	free((*node)->var);
	free((*node)->val);
	free(*node);
	*node = NULL;
	return (0);
}
