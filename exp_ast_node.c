#include "exp_ast_node.h"

int			is_exp(t_token *t)
{
	return (strcmp(t->data, "**") == 0);
}

static int	exp_exec(t_ast *self)
{
	int	left_operand;
	int	right_operand;

	left_operand = self->left->exec(self->left);
	right_operand = self->right->exec(self->right);
	return (pow(left_operand, right_operand));
}

t_ast		*create_exp_node(void)
{
	t_ast	*new;

	new = calloc(sizeof(t_ast), 1);
	new->exec = exp_exec;
	new->data = strdup("**");
	new->priority = 1;
	return (new);
}
