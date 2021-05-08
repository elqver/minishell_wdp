#include "ast.h"

int		num_exec(t_ast *self)
{
	return ((int)(self->data - '0'));
}

t_ast	*create_num_node(char data)
{
	t_ast	*new;

	new = calloc(sizeof(t_ast), 1);
	new->exec = num_exec;
	new->data = data;
	new->priority = 2;
	return (new);
}

int		is_num(t_token *t)
{
	return (isdigit(t->data[0]));
}

int		plus_exec(t_ast *self)
{
	int	left_operand;
	int	right_operand;
	int	operator;

	left_operand = self->left->exec(self->left);
	right_operand = self->right->exec(self->right);
	return (left_operand + right_operand);
}

t_ast	*create_plus_node(void)
{
	t_ast	*new;

	new = calloc(sizeof(t_ast), 1);
	new->exec = plus_exec;
	new->data = '+';
	new->priority = 0;
	return (new);
}

int		is_plus(t_token *t)
{
	return (t->data[0] == '+');
}

int		mult_exec(t_ast *self)
{
	int	left_operand;
	int	right_operand;
	int	operator;

	left_operand = self->left->exec(self->left);
	right_operand = self->right->exec(self->right);
	return (left_operand * right_operand);
}

t_ast	*create_mult_node(void)
{
	t_ast	*new;

	new = calloc(sizeof(t_ast), 1);
	new->exec = mult_exec;
	new->data = '*';
	new->priority = 1;
	return (new);
}

int		is_mult(t_token *t)
{
	return (t->data[0] == '*');
}

t_ast	*create_node_by_token(t_token *t)
{
	if (is_num(t))
		return (create_num_node(t->data[0]));
	if (is_mult(t))
		return (create_mult_node());
	if (is_plus(t))
		return (create_plus_node());
	return (NULL);
}

t_ast	*insert(t_ast **root, t_ast **current, t_ast *node)
{
	if (root == NULL || current == NULL)
		return (NULL);
	if (*root == NULL || *current == NULL)
	{
		*root = node;
		*current = node;
		return (node);
	}
	if (node->priority > (*current)->priority)
	{
		if ((*current)->right != NULL)
		{
			printf("Right not empty\n");
			return (NULL);
		}
		(*current)->right = node;
	}
}

t_ast	*build_ast(t_token *t)
{
	t_ast	*root = NULL;
	t_ast	*current = NULL;
	t_ast	*node_to_insert = NULL;

	while (t != NULL)
	{
		node_to_insert = create_node_by_token(t);
		if (insert(&root, &current, node_to_insert) == NULL)
		{
			printf("Error while inserting node to ast\n");
			return (NULL);
		}
		t = t->next;
	}
	return (root);
}
