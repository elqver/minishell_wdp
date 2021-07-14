#include "command_commands.h"
#include "../tokenizer/tokenizer.h"
#include "../utils/utils.h"

<<<<<<< HEAD
int	get_type_of_redir(char *redir)
{
	if (ft_strncmp(redir, "<<", 2) == 0)
		return (TWO_LEFT_REDIR);
	if (ft_strncmp(redir, ">>", 2) == 0)
		return (TWO_RIGHT_REDIR);
	if (ft_strncmp(redir, "<", 1) == 0)
		return (ONE_LEFT_REDIR);
	if (ft_strncmp(redir, ">", 1) == 0)
		return (ONE_RIGHT_REDIR);
	return (0);
}

=======
>>>>>>> f4960ae9bbf3e6b6db9c0ed6dede2deeb0034ed3
static int	one_left_redir(t_ast *self)
{
	int	fd;

	fd = open(self->left->data, O_RDONLY);
	if (fd < 0)
		return (1);
	dup2(fd, 0);
	close(fd);
	return (0);
}

static int	one_right_redir(t_ast *self)
{
	int	file_fd;

	file_fd = open(self->left->data, O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (file_fd < 0)
		return (1);
	dup2(file_fd, 1);
	close(file_fd);
	return (0);
}

static int	two_right_redir(t_ast *self)
{
	int	file_fd;

	file_fd = open(self->left->data, O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (file_fd < 0)
		return (1);
	dup2(file_fd, 1);
	close(file_fd);
	return (0);
}

static int	two_left_redir(t_ast *self)
{
	int	new_fd_stdin;

	new_fd_stdin = ft_atoi(self->left->data); 
	dup2(new_fd_stdin, 0);
	close(new_fd_stdin);
	self->right->exec(self->right);
	return (0);
}

int	redir_exec(t_ast *self)
{
	if (self == NULL || self->right == NULL)
		return (0);
	else if (strncmp(self->data, "<<", 2) == 0)
		two_left_redir(self);
	else if (strncmp(self->data, ">>", 2) == 0)
		two_right_redir(self);
	else if (strncmp(self->data, "<", 1) == 0)
		one_left_redir(self);
	else if (strncmp(self->data, ">", 1) == 0)
		one_right_redir(self);
<<<<<<< HEAD
	if (redir_type == TWO_RIGHT_REDIR)
		two_right_redir(self);
	if (redir_type == TWO_LEFT_REDIR)
		two_left_redir(self);
	if (self->right)
	{
		self->right->exec(self->right);
		return (1);
	}
	return (0);
}

t_ast	*create_redir_node(t_token *token)
{
	t_ast	*redir_node;

	redir_node = calloc(sizeof(t_ast), 1);
	redir_node->priority = REDIR_P;
	redir_node->exec = redir_exec;
	redir_node->data = ft_strdup(token->data); 
	return (redir_node);
=======
	else
		return (0);
	self->right->exec(self->right);
	return (1);
>>>>>>> f4960ae9bbf3e6b6db9c0ed6dede2deeb0034ed3
}
