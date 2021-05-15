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
	if (node == NULL)
		return (NULL);
	node->data = strdup(token->data);
	node->type = token->type;
	node->priority = token->priority;
	return (node);
}

t_child_list	*create_child_list(t_ast *child)
{
	t_child_list	*node;

	node = malloc(sizeof(t_child_list));
	if (node == NULL)
		return (NULL);
	node->child = child;
	node->next = NULL;
	return (node);
}

static t_ast	*append_child_list(t_ast *parent, t_ast *child)
{
	t_child_list	*ptr;

	if (parent == NULL || child == NULL)
		return (NULL);
	if (parent->child_list == NULL)
	{
		parent->child_list = create_child_list(child);
		if (parent->child_list)
			return (parent);
		return (NULL);
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
	if (node == NULL)
		return (node);
	node->type = COMMAND;
	node->priority = COMMAND_P;
	return (node);
}

static t_ast	*insert_first_node(t_ast **root, t_ast **current, t_ast *node)
{
	if (node->priority != ARG_P)
	{
		printf("Line should begin with a command! Error occured.\n"); //Replace it with allowd function later;
		return (NULL);
	}
	*root = create_command_node();
	if (*root == NULL)
		return (NULL);
	*current = *root;
	if (append_child_list(*root, node) == NULL)
	{
		free(root);
		return (NULL);
	}

	return (*root);
}

static t_ast	*insert_word_node(t_ast **root, t_ast **current, t_ast *node)
{
	t_ast	*tmp;

	tmp = create_command_node();
	if (tmp == NULL)
		return (NULL);
	if (append_child_list(*current, tmp) == NULL)
	{
		free(tmp);
		return (NULL);
	}
	tmp->parent = *current;
	*current = tmp;
	node->parent = tmp;
	if (append_child_list(*current, node) == NULL)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

static t_ast	*insert_pipe_node(t_ast **root, t_ast **current, t_ast *node)
{
	if (get_last_child((*current)->child_list)->type == REDIR)
		return (NULL);
	if ((*current)->parent == NULL)
		(*root) = node;
	node->parent = (*current)->parent;
	if (node->parent != NULL)
		node->parent->child_list->next->child = node;
	(*current)->parent = node;
	if (append_child_list(node, *current) == NULL)
		return (NULL);
	*current = node;
	return (node);
}

static t_ast	*insert(t_ast **root, t_ast **current, t_ast *node)
{
	if (root == NULL || current == NULL)
		return (NULL);
	if (*root == NULL || *current == NULL)
		return (insert_first_node(root, current, node));
	if (node->priority == ARG_P && (*current)->priority == COMMAND_P)
		return (append_child_list(*current, node));
	if (node->priority == ARG_P && (*current)->priority == PIPE_P)
		return (insert_word_node(root, current, node));
	if (node->priority == PIPE_P && (*current)->priority == COMMAND_P)
		return (insert_pipe_node(root, current, node));
	return (NULL);
}

static int		is_last_token_valid(t_token *token)
{
	t_token	*last_token;

	last_token = get_last_token(token);
	if (last_token->type == PIPE)
	{
		printf ("last pipe have not right argument! Error occured.\n");
		return (0);
	}
	if (last_token->type == REDIR)
	{
		printf( "last redirection have not right argument! Error occured.\n");
		return (0);
	}
	return (1);	
}

t_ast			*build_ast(t_token *token)
{
	t_ast	*root = NULL;
	t_ast	*current = NULL;
	t_ast	*node_to_insert = NULL;

	if (!is_last_token_valid(token))
		return (NULL);
	while (token != NULL)
	{
		node_to_insert = create_ast_node(token);
		if (node_to_insert == NULL)
		{
			if (root != NULL)
				destroy_ast(root);
			return (NULL);
		}
		if (insert(&root, &current, node_to_insert) == NULL)
		{
			if (root != NULL)
				destroy_ast(root);
			printf("Error while inserting node to ast\n");
			return (NULL);
		}
		token = token->next;
	}
	return root;
}

void	free_child_list(t_child_list *t)
{
	t_child_list	*tmp;

	tmp = t;
	while (t != NULL)
	{
		tmp = t;	
		free(t);
		t = tmp->next;
	}
}

t_ast	*get_last_child(t_child_list *child_list)
{
	if (child_list == NULL)
		return (NULL);
	while (child_list->next != NULL)
		child_list = child_list->next;
	return (child_list->child);
}

void	destroy_ast(t_ast *ast)
{
	t_child_list	*tmp_child_list;

	if (ast == NULL)
		return ;
	tmp_child_list = ast->child_list;
	while (tmp_child_list != NULL)
	{
		destroy_ast(tmp_child_list->child);
		tmp_child_list = tmp_child_list->next;
	}
	free(ast->parent);
	free_child_list(ast->child_list);
	free(ast->data);
}
