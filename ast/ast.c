#include "ast.h"
#include "../command/command_commands.h"

static int	is_ast_valid(t_ast *ast)
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

void	execute_ast(void)
{
	t_ast	*self;

	self = get_ast();
	if (self == NULL)
		return ;
	switch_to_command_mode();
	self->exec(self);
}

t_ast	*build_ast(t_token *token)
{
	t_ast	*root;

	root = NULL;
	while (token != NULL)
	{
		if (insert_ast_node(&root, create_ast_node(token)) == NULL)
			return (set_ast(destroy_ast(root)));
		token = token->next;
	}
	if (!is_ast_valid(root))
		return (set_ast(destroy_ast(root)));
	return (set_ast(root));
}
