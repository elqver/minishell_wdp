#include "command_pipe.h"

static int	substitution_in(t_ast *node, int fd_redirect[2])
{
	int child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		close(fd_redirect[1]);
		dup2(fd_redirect[0], 0);
		close(fd_redirect[0]); //Is this one important?
		node->execute(node);
		exit(1); //process should not get here
	}
	return (child_pid);
}

static int	substitution_out(t_ast *node, int fd_redirect[2])
{
	int child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		close(fd_redirect[0]);
		dup2(fd_redirect[1], 1);
		close(fd_redirect[1]); //Is this one important?
		node->execute(node);
	}
	return (child_pid);
}

static int	pipe_exec(t_ast *self)
{
	int	fd_redirect[2];

	substitution_in(self->left, fd_redirect);	
	substitution_out(self->right, fd_redirect);	
	wait(NULL);
	wait(NULL);
	exit(0);
}

t_ast		*create_pipe_node()
{
	t_ast	*pipe_node;

	pipe_node = calloc(sizeof(t_ast), 1);
	pipe_node->priority = 1;
	pipe_node->execute = pipe_exec;
	pipe_node->data = strdup("|"); //Replace this with ft

	return (pipe_node);
}
