#include "ast.h"
#include "ast_node.h"

static void		print_tab(int pref_len)
{
	printf("|");
	while (pref_len--)
		printf("\t|");
}

void			print_ast(t_ast *root, int pref_len)
{
	if (root == NULL)
	{
		printf("Taki ti ne ochen: root = NULL\n");
		return ;
	}
	print_tab(pref_len);
	printf("Node data: %c %p\n", root->data, root);
	if (root->left != NULL)
	{
		print_tab(pref_len);
		printf("LEFT {\n");
		print_ast(root->left, pref_len + 1);
		print_tab(pref_len);
		printf("}\n");
	}
	if (root->right != NULL)
	{
		print_tab(pref_len);
		printf("RIGHT {\n");
		print_ast(root->right, pref_len + 1);
		print_tab(pref_len);
		printf("}\n");
	}
}

static t_ast	*insert_lower(t_ast **root, t_ast **current, t_ast *node)
{
	(void) root;
	if ((*current)->right != NULL)
		return (NULL);
	(*current)->right = node;
	node->parent = *current;
	*current = node;
	return (node);
}

static t_ast	*insert_higher(t_ast **root, t_ast **current, t_ast *node)
{
	while ((*current)->parent != NULL && (*current)->priority < node->priority)
		*current = (*current)->parent;

	if ((*current)->priority > node->priority)
	{
		node->left = (*current)->right;
		(*current)->right = node;
		node->parent = *current;
		(*current) = node;
		return (*root);
	}
	if ((*current)->parent == NULL)
	{
		node->left = *current;
		node->left->parent = node;
		*root = node;
		*current = node;
		return (*root);
	}
	if ((*current)->priority == node->priority)
	{
		node->left = (*current)->right;
		node->parent = *current;
		(*current)->right = node;
		*current = node;
		return (*root);
	}
	return (NULL);
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

	if (current->priority != 0)
	{
		printf("Error: unexpected EOF\n");
		return (NULL);
	}

	return (root);
}
