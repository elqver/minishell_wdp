#include "ast.h"
#include "../command/command_commands.h"

t_ast	*insert_ast_node(t_ast **ast, t_ast *node)
{
	if (ast == NULL || node == NULL)
		return (NULL);
	if ((*ast) == NULL)
		return (*ast = node);
	if ((*ast)->priority < node->priority)
	{
		node->right = (*ast);
		(*ast) = node;
	}
	else if ((*ast)->priority == PIPE_P)
		insert_ast_node(&((*ast)->left), node);
	else if ((*ast)->priority == node->priority)
		insert_ast_node(&((*ast)->right), node);
	else if ((*ast)->priority > node->priority)
	{
		if ((*ast)->left == NULL)
			insert_ast_node(&((*ast)->left), node);
		else
			insert_ast_node(&((*ast)->right), node);
	}
	return (*ast);
}
