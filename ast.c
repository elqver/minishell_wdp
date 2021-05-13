#include "ast.h"
#include "tokenizer.h"

static t_ast	*create_ast_node(t_token *token)
{
	t_ast	*node;

	node = calloc(sizeof(t_ast), 1);
	node->type = token->type;
	node->priority = token->priority;

	
	return (node);
}

static t_ast	*insert(t_ast **root, t_ast **current, t_ast *node)
{
	if (root == NULL || current == NULL)
		return (NULL);
	if (*root == NULL || *current == NULL)
	{
		*root = node;
		*current = node;
		return (node);
	}
	
	return (NULL);
}
	

t_ast			*build_ast(t_token *token)
{
	t_ast	*root = NULL;
	t_ast	*current = NULL;
	t_ast	*node_to_insert = NULL;

	while (token != NULL)
	{
		node_to_insert = create_ast_node(token);
		if (insert(&root, &current, node_to_insert) == NULL)
		{
			printf("Error while inserting node to ast\n");
			return (NULL);
		}
		token = token->next;
	}

	return root;
}
