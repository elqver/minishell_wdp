#include "command_commands.h"
#include "../builtins/builtins.h"

t_ast	*create_command_node(t_token *token)
{
	t_ast	*command_node;

	command_node = calloc(sizeof(t_ast), 1);
	command_node->priority = 1;
	command_node->exec = execute_command;
	command_node->data = strdup(token->data); //Replace this with ft
	command_node->priority = ARG_P;
	return (command_node);
}

t_ast	*create_pipe_node(void)
{
	t_ast	*pipe_node;

	pipe_node = calloc(sizeof(t_ast), 1);
	pipe_node->priority = PIPE_P;
	pipe_node->exec = pipe_exec;
	pipe_node->data = strdup("|"); //Replace this with ft
	return (pipe_node);
}

t_ast	*create_redir_node(t_token *token)
{
	t_ast	*redir_node;

	redir_node = calloc(sizeof(t_ast), 1);
	redir_node->priority = REDIR_P;
	redir_node->exec = redir_exec;
	redir_node->data = strdup(token->data); //Replace this with ft_
	return (redir_node);
}
