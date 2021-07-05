#include "ast.h"
#include "../tokenizer/tokenizer.h"
#include "../command/command_commands.h"

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
	if (root == NULL)
	{
		printf("Taki ti ne ochen: root = NULL\n");
		return ;
	}
	print_tab(pref_len);
	white();
	printf("Node data: %s\n", root->data);
	choose_color(pref_len);
	if (root->left != NULL)
	{
		print_tab(pref_len);
		printf("LEFT {\n");
		print_ast(root->left, pref_len + 1);
		print_tab(pref_len);
		printf("}\n");
	}
	choose_color(pref_len);
	if (root->right != NULL)
	{
		print_tab(pref_len);
		printf("RIGHT {\n");
		print_ast(root->right, pref_len + 1);
		print_tab(pref_len);
		printf("}\n");
	}
}

static t_ast	*create_ast_node(t_token *token)
{
	if (token->priority == PIPE_P)
		return (create_pipe_node());
	if (token->priority == ARG_P)
		return (create_command_node(token));
	if (token->priority == REDIR_P)
		return (create_redir_node(token));
	return (NULL);
}

static t_ast	*insert(t_ast **ast, t_ast *node)
{
	if (ast == NULL || node == NULL)
		return (NULL);
	if ((*ast) == NULL)
	{
		*ast = node;
		return (node);
	}
	if ((*ast)->priority < node->priority)
	{
		node->right = (*ast);
		(*ast) = node;
	}
	else if ((*ast)->priority == PIPE_P)
		insert(&((*ast)->left), node);
	else if ((*ast)->priority == node->priority)
		insert(&((*ast)->right), node);
	else if ((*ast)->priority > node->priority)
	{
		if ((*ast)->left == NULL)
			insert(&((*ast)->left), node);
		else
			insert(&((*ast)->right), node);
	}
	return (*ast);
}

int				is_ast_valid(t_ast *ast)
{
	if (ast == NULL)
		return (1);
	if (ast->priority == PIPE_P)
		if (!(ast->left && ast->right))
			return (0);
	if (ast->priority == REDIR_P)
		if (!(ast->left))
			return (0);
	if (ast->priority == ARG_P)
		if (ast->left)
			return (0);
	return (is_ast_valid(ast->left) && is_ast_valid(ast->right));
}

void	*destroy_ast(t_ast *ast)
{
	if (ast == NULL)
		return (NULL);
	destroy_ast(ast->left);
	destroy_ast(ast->right);
	free(ast->data);
	free(ast);
	return (NULL);
}

t_ast			*build_ast(t_token *token)
{
	t_ast	*root;
	t_ast	*node_to_insert;

	root = NULL;
	while (token != NULL)
	{
		if (insert(&root, create_ast_node(token)) == NULL)
			return (NULL);
		token = token->next;
	}
	if (!is_ast_valid(root))
		return (destroy_ast(root));
	return root;
}
