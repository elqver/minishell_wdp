#include "command_commands.h"
#include <sys/wait.h>

static int	substitution_in(t_ast *node, int fd_redirect[2], char **envp)
{
	int child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		close(fd_redirect[1]);
		dup2(fd_redirect[0], 0);
		close(fd_redirect[0]);
		node->exec(node, envp);
		exit(1);
	}
	return (child_pid);
}

static int	substitution_out(t_ast *node, int fd_redirect[2], char **envp)
{
	int child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		close(fd_redirect[0]);
		dup2(fd_redirect[1], 1);
		close(fd_redirect[1]);
		node->exec(node, envp);
		exit(1);
	}
	return (child_pid);
}

static int	pipe_exec(t_ast *self, char **envp)
{
	int	fd_redirect[2];
	int	left_pid;
	int	right_pid;

	pipe(fd_redirect);
	left_pid = substitution_in(self->left, fd_redirect, envp);	
	right_pid = substitution_out(self->right, fd_redirect, envp);
	close(fd_redirect[0]);
	close(fd_redirect[1]);
	waitpid(right_pid, NULL, 0);
	waitpid(left_pid, NULL, 0);
	exit(0);
}

t_ast		*create_pipe_node()
{
	t_ast	*pipe_node;

	pipe_node = calloc(sizeof(t_ast), 1);
	pipe_node->type = PIPE;
	pipe_node->priority = PIPE_P;
	pipe_node->exec = pipe_exec;
	pipe_node->data = strdup("|"); //Replace this with ft

	return (pipe_node);
}
