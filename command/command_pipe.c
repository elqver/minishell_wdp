#include "command_commands.h"

static int	substitution_in(t_ast *node, int fd_redirect[2])
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		close(fd_redirect[1]);
		dup2(fd_redirect[0], 0);
		close(fd_redirect[0]);
		node->exec(node);
		exit(1);
	}
	return (child_pid);
}

static int	substitution_out(t_ast *node, int fd_redirect[2])
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		close(fd_redirect[0]);
		dup2(fd_redirect[1], 1);
		close(fd_redirect[1]);
		node->exec(node);
		exit(1);
	}
	return (child_pid);
}

int	pipe_exec(t_ast *self)
{
	int	fd_redirect[2];
	int	left_pid;
	int	right_pid;

	pipe(fd_redirect);
	right_pid = substitution_out(self->right, fd_redirect);
	left_pid = substitution_in(self->left, fd_redirect);
	close(fd_redirect[0]);
	close(fd_redirect[1]);
	waitpid_logging(right_pid);
	waitpid_logging(left_pid);
	return (0);
}
