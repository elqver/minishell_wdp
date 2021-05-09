#include "div_ast_node.h"

int			is_div(t_token *t)
{
	return (t->data[0] == '/');
}

static int	div_exec(t_ast *self)
{
	int	left_operand;
	int	right_operand;

	left_operand = self->left->exec(self->left);
	right_operand = self->right->exec(self->right);
	return (left_operand / right_operand);
}


t_ast		*create_div_node(void)
{
	t_ast	*new;

	new = calloc(sizeof(t_ast), 1);
	new->exec = div_exec;
	new->data = strdup("/");
	new->priority = 2;
	return (new);
}
