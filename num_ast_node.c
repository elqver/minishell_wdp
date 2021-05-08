#include "num_ast_node.h"

static int	num_exec(t_ast *self)
{
	return ((int)(self->data - '0'));
}

t_ast		*create_num_node(char data)
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
	return (isdigit(t->data[0]));
}
