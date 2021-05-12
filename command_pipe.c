#include "command_pipe.h"

static int	first_child(t_ast *self, int fd_redirect[2])
{
	int first_child_pid;

	first_child_pid = fork();
	if (first_child_pid == -1)
	{
		printf("Could not fork\n");
		return (1);
	}
	if (first_child_pid == 0)
	{
		close(fd_redirect[1]);
		dup2(fd_redirect[0], 1);
		if (self->left->execute(self->left))
		{
			printf("left child error occured\n");
			return (1);
		}
	}
	return (first_child_pid);
}

static int	second_child(t_ast *self, int fd_redirect[2])
{
	int	second_child_pid;
	
	second_child_pid = fork();
	if (second_child_pid == -1)
	{
		printf("Could not fork\n");
		return (1);
	}
	if (second_child_pid == 0)
	{
		close(fd_redirect[0]);
		dup2(fd_redirect[1], 0);
		if (self->right->execute(self->right))
		{
			printf("right child error occured\n");
			return (1);
		}
	}
	return (second_child_pid);
}

static int	pipe_exec(t_ast *self)
{
	int	fd_redirect[2];

	if (pipe(fd_redirect) == -1)
	{
		printf("Pipe could not been created\n");
		return (1);
	}
	first_child(self, fd_redirect);	
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
	pipe_node->command_name = strdup("|"); //Replace this with ft

	return (pipe_node);
}
