#include "ast.h"
#include "../tokenizer/tokenizer.h"
#include "../command/command_commands.h"
#include <readline/readline.h>
#include <readline/history.h>

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
	white();
}

t_ast	*ast_singleton(t_ast *new_ast, int is_set)
{
	static t_ast	*saved_ast;

	if (is_set)
	{
		destroy_ast(saved_ast);
		saved_ast = new_ast;
	}
	return (saved_ast);
}

t_ast	*get_ast(void)
{
	return (ast_singleton(NULL, 0));
}

t_ast	*set_ast(t_ast *new_ast)
{
	return (ast_singleton(new_ast, 1));
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

static int	has_quotes(char *line)
{
	while (*line)
	{
		if (single_quote_condition(*line) || double_quote_condition(*line))
			return (1);
		line++;
	}
	return (0);
}

static void	heredoc(char *delimeter, int env_subst_needed, int *fd_here)
{
	char	*line_read;

	line_read = readline("> ");
	while (strcmp(line_read, delimeter)) // TODO: replace later
	{
		if (env_subst_needed)
			handle_envs(&line_read);
		write(fd_here[1], line_read, strlen(line_read)); // TODO: replace later
		write(fd_here[1], "\n", 1); // TODO: replace later
		free(line_read);
		line_read = readline("> ");
	}
	free(line_read);
}

static void		handle_heredoc_node(t_ast *self)
{
	char	*delimeter;
	int		fd_redirect[2];
	int		env_subst_needed;

	restore_original_file_descriptors();
	delimeter = self->left->data;
	env_subst_needed = !has_quotes(delimeter);
	resect_quotes_from_line(&delimeter);
	pipe(fd_redirect);
	heredoc(delimeter, env_subst_needed, fd_redirect);
	close(fd_redirect[1]);
	free(self->left->data);
	self->left->data = malloc(3);
	sprintf(self->left->data, "%d", fd_redirect[0]);
}

static void	recursive_handle_heredocs(t_ast	*self)
{
	if (self == NULL)
		return ;
	if (self->right != NULL)
		recursive_handle_heredocs(self->right);
	if (self->left != NULL)
		recursive_handle_heredocs(self->left);
	if (strncmp(self->data, "<<", 2) == 0)
		handle_heredoc_node(self);
}

void		handle_heredocs()
{
	recursive_handle_heredocs(get_ast());
}

void		execute_abstract_syntax_tree(void)
{
	get_ast()->exec(get_ast());
}

t_ast		*build_ast(t_token *token)
{
	t_ast	*root;

	root = NULL;
	print_token_list(token);
	while (token != NULL)
	{
		printf("TOKEN DATA TO INSERT = |%s|\n", token->data);
		if (insert(&root, create_ast_node(token)) == NULL)
			return (set_ast(destroy_ast(root)));
		token = token->next;
	}
	if (!is_ast_valid(root))
		return (set_ast(destroy_ast(root)));
	print_ast(root, 0);
	return (set_ast(root));
}
