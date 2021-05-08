#include "ast.h"
#include "ast_node.h"

void			print_ast(t_ast *root)
{
	if (root == NULL)
	{
		printf("Taki ti ne ochen: root = NULL\n");
		return ;
	}
	printf("Node data: %c\n", root->data);
	if (root->left != NULL)
	{
		printf("LEFT {\n");
		print_ast(root->left);
		printf("}\n");
	}
	if (root->right != NULL)
	{
		printf("RIGHT {\n");
		print_ast(root->right);
		printf("}\n");
	}
}

static t_ast	*insert_lower(t_ast **root, t_ast **current, t_ast *node)
{
	(void) root;
	if ((*current)->right != NULL)
	{
		printf("Right not empty\n");
		print_ast(*root);
		return (NULL);
	}
	(*current)->right = node;
	node->parent = *current;
	*current = node;
	return (node);
}

static t_ast	*insert_higher(t_ast **root, t_ast **current, t_ast *node)
{
	/*
	if ((*current)->priority > node->priority)
	{
		*current = (*current)->parent;
		insert_higher(root, current, node);
		return (*root);
	}
	*/
	while ((*current)->parent != NULL && (*current)->priority < node->priority)
	{
		*current = (*current)->parent;
	}
	if ((*current)->priority > node->priority)
	{
		node->left = (*current)->right;
		(*current)->right = node;
		(*current) = node;
		return (*root);
	}
	*root = node;
	node->left = *current;
	*current = node;
	return (*root);
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
	if (node->priority < (*current)->priority)
		return (insert_lower(root, current, node));
	if (node->priority > (*current)->priority)
		return (insert_higher(root, current, node));
	return (NULL);
}

t_ast			*build_ast(t_token *t)
{
	t_ast	*root = NULL;
	t_ast	*current = NULL;
	t_ast	*node_to_insert = NULL;

	while (t != NULL)
	{
		node_to_insert = create_node_by_token(t);
		if (node_to_insert == NULL)
		{
			printf("Error creating node\n");
			return (NULL);
		}
		if (insert(&root, &current, node_to_insert) == NULL)
		{
			printf("Error while inserting node to ast\n");
			return (NULL);
		}
		t = t->next;
	}
	return (root);
}

