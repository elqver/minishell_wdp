#include "ast.h"
#include "../command/command_commands.h"

t_ast	*create_ast_node(t_token *token)
{
	if (token->priority == PIPE_P)
		return (create_pipe_node());
	if (token->priority == ARG_P)
		return (create_command_node(token));
	if (token->priority == REDIR_P)
		return (create_redir_node(token));
	return (NULL);
}
