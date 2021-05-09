#include "num_ast_node.h"

static int	num_exec(t_ast *self)
{
	return (atoi(self->data));
}

t_ast		*create_num_node(char *data)
{
	t_ast	*new;

	new = calloc(sizeof(t_ast), 1);
	new->exec = num_exec;
	new->data = data;
	new->priority = 0;
	return (new);
}

int			is_num(t_token *t)
{
	size_t	i;

	i = 0;
	while (isdigit(t->data[i]))
		i++;
	if (t->data[i] == '\0')
		return (1);
	return (0);
}
