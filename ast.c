#include "ast.h"
#include "tokenizer.h"

# define RED "\033[0;31m"
# define YEL "\033[0;33m"
# define GRE "\033[0;32m"
# define WHI "\033[0;37m"

static void		red(void)
{
	printf(RED);
}

static void		yellow(void)
{
	printf(YEL);
}

static void		green(void)
{
	printf(GRE);
}

static void		white(void)
{
	printf(WHI);
}

static void		choose_color(int p)
{
	if (p % 3 == 0)
		green();
	else if (p % 3 == 1)
		red();
	else
		yellow();
}

static void		print_tab(int pref_len)
{
	int p = pref_len;
	white();
	printf("|");
	while (pref_len--)
		printf("\t|");
	choose_color(p);
}

void			print_ast(t_ast *root, int pref_len)
{
	t_child_list	*tmp_child;
	if (root == NULL)
	{
		printf("Taki ti ne ochen: root = NULL\n");
		return ;
	}
	white();
	print_tab(pref_len);
	printf("Node type: %d\n", root->type);
	print_tab(pref_len);
	printf("Node priority: %d\n", root->priority);
	print_tab(pref_len);
	if (root->data)
		printf("Node data: %s\n", root->data);
	else
		printf("Node data: NULL\n");
	choose_color(pref_len);

	tmp_child = root->child_list;	
	while (tmp_child != NULL)
	{
		print_tab(pref_len);
		printf("Child: {\n");
		print_ast(tmp_child->child, pref_len + 1);
		print_tab(pref_len);
		printf("}\n");
		tmp_child = tmp_child->next;
	}
	white();
}

static t_ast	*create_ast_node(t_token *token)
{
	t_ast	*node;

	node = calloc(sizeof(t_ast), 1);
	node->data = strdup(token->data);
	node->type = token->type;
	node->priority = token->priority;
	return (node);
}

t_child_list	*create_child_list(t_ast *child)
{
	t_child_list	*node;

	node = malloc(sizeof(t_child_list));
	node->child = child;
	node->next = NULL;
	return (node);
}

static t_ast	*append_child_list(t_ast *parent, t_ast *child)
{
	t_child_list	*ptr;

	if (parent->child_list == NULL)
	{
		parent->child_list = create_child_list(child);
		return (parent);
	}
	ptr = parent->child_list;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = create_child_list(child);
	return (parent);
}

static t_ast	*create_command_node(void)
{
	t_ast	*node;

	node = calloc(sizeof(t_ast), 1);
	node->type = COMMAND;
	node->priority = COMMAND_P;
	return (node);
}

static t_ast	*insert(t_ast **root, t_ast **current, t_ast *node)
{
	t_ast	*tmp;

	if (root == NULL || current == NULL)
		return (NULL);
	if (*root == NULL || *current == NULL)
	{
		if (node->priority != ARG_P)
		{
			printf("TY NE PRAV\n");
			return (NULL);
		}
		*root = create_command_node();
		*current = *root;
		append_child_list(*root, node);
		return (*root);
	}
	if (node->priority == ARG_P)
	{
		if ((*current)->priority == COMMAND_P)
			return (append_child_list(*current, node));
		if ((*current)->priority == PIPE_P)
		{
			tmp = create_command_node();
			append_child_list(*current, tmp);
			tmp->parent = *current;
			*current = tmp;
			node->parent = tmp;
			return (append_child_list(*current, node));
		}
	}
	if (node->priority == PIPE_P && (*current)->priority == COMMAND_P)
	{
		if ((*root)->priority < node->priority)
			(*root) = node;
		node->parent = (*current)->parent;
		if (node->parent != NULL)
			node->parent->child_list->next->child = node;
		(*current)->parent = node;
		append_child_list(node, *current);
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
