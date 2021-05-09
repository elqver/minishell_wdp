#include "sub_ast_node.h"

int			is_sub(t_token *t)
{
	return (t->data[0] == '-');
}

static int	sub_exec(t_ast *self)
{
	int	left_operand;
	int	right_operand;

	left_operand = self->left->exec(self->left);
	right_operand = self->right->exec(self->right);
	return (left_operand - right_operand);
}

t_ast		*create_sub_node(void)
{
	t_ast	*new;

	new = calloc(sizeof(t_ast), 1);
	new->exec = sub_exec;
	new->data = strdup("-");
	new->priority = 3;
	return (new);
}
