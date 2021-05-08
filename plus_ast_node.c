#include "plus_ast_node.h"

static int	plus_exec(t_ast *self)
{
	int	left_operand;
	int	right_operand;

	left_operand = self->left->exec(self->left);
	right_operand = self->right->exec(self->right);
	return (left_operand + right_operand);
}

t_ast		*create_plus_node(void)
{
	t_ast	*new;

	new = calloc(sizeof(t_ast), 1);
	new->exec = plus_exec;
	new->data = '+';
	new->priority = 2;
	return (new);
}

int			is_plus(t_token *t)
{
	return (t->data[0] == '+');
}

