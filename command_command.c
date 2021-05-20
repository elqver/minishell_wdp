#include "command_command.h"

static int	command_exec(t_ast *self)
{
	char *tmp_1;
	char *tmp_2;

	tmp_1 = NULL;
	tmp_2 = NULL;
	execve(self->data, &tmp_1, &tmp_2);
	return (0xDEFEC8);
}

t_ast		*create_command_node(t_token *token)
{
	t_ast	*command_node;

	command_node = calloc(sizeof(t_ast), 1);
	command_node->priority = 1;
	command_node->execute = command_exec;
	command_node->data = strdup(token->data); //Replace this with ft

	return (command_node);
}
