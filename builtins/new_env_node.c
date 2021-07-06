#include "env.h"

t_env	*new_env_node(char *var, char *val)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->var = strdup(var); // TODO: replace with ft_ and check for NULL
	new->val = strdup(val); // TODO: replace with ft_
	new->next = NULL;
	return (new);
}
