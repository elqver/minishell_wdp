#include "env.h"
#include "../utils/utils.h"

t_env	*new_env_node(char *var, char *val)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->var = ft_strdup(var);
	if (val != NULL)
		new->val = ft_strdup(val);
	else
		new->val = NULL;
	new->next = NULL;
	return (new);
}
