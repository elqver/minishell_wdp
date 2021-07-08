#include "command_commands.h"
#include <ctype.h> //???
#include <fcntl.h>

/* //////////////////////////////////////////////////////////////////// */
/*																		*/
/*							МИША МИША МИША								*/
/*					Я УБРАЛ ВОЗМОЖНОСТЬ РЕДИРЕКТА 						*/
/*					КОНКРЕТНОГО ПОТОКА В НАШЕМ ШЕЛЛЕ.					*/
/*																		*/
/*					НАДО ЧТО-ТО СДЕЛАТЬ С								*/
/*					get_fd_of_redir()									*/
/*																		*/
/* //////////////////////////////////////////////////////////////////// */

int			get_fd_of_redir(char *redir)
{
	if (!isdigit(*redir)) //???
		return (-1);
	return (atoi(redir));
}

/*
int			get_type_of_redir(char *redir)
{
	while (isdigit(*redir))
		redir++;
	if (!strcmp("<", redir))
		return (ONE_LEFT_REDIR);
	if (!strcmp(">>", redir))
		return (TWO_RIGHT_REDIR);
	return (ONE_RIGHT_REDIR);
}
*/

int	get_type_of_redir(char *redir)
{
	if (strncmp(redir, "<", 1) == 0)
		return (ONE_LEFT_REDIR);
	if (strncmp(redir, "<<", 2) == 0)
		return (TWO_LEFT_REDIR);
	if (strncmp(redir, ">", 1) == 0)
		return (ONE_RIGHT_REDIR);
	if (strncmp(redir, ">>", 2) == 0)
		return (TWO_RIGHT_REDIR);
	return (0);
}

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

static int	two_left_redir(t_ast *self)
{
	int	command_fd;
}

static int	one_right_redir(t_ast *self)
{
	int	redir_fd;
	int file_fd;

	redir_fd = get_fd_of_redir(self->data);
	if (redir_fd == -1)
		redir_fd = 1;
	file_fd = open(self->left->data, O_WRONLY | O_CREAT, S_IWUSR | S_IXGRP);
	if (file_fd < 0)
		return (1);
	dup2(file_fd, redir_fd);
	close(file_fd);
	return (0);
}

static int	two_right_redir(t_ast *self)
{
	int	redir_fd;
	int file_fd;

	redir_fd = get_fd_of_redir(self->data);
	if (redir_fd == -1)
		redir_fd = 1;
	file_fd = open(self->left->data, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (file_fd < 0)
		return (1);
	dup2(file_fd, redir_fd);
	close(file_fd);
	return (0);
}

static int	two_left_redit(t_ast *self)
{
	int	redir_fd;
	int	file_fd;

}

static int	redir_exec(t_ast *self)
{
	int	redir_type;

	redir_type = get_type_of_redir(self->data);
	if (redir_type == ONE_LEFT_REDIR)
		one_left_redir(self);
	if (redir_type == ONE_RIGHT_REDIR)
		one_right_redir(self);
	if (redir_type == TWO_RIGHT_REDIR)
		two_right_redir(self);
	self->right->exec(self->right);
	return (1);
}

t_ast		*create_redir_node(t_token *token)
{
	t_ast	*redir_node;

	redir_node = calloc(sizeof(t_ast), 1);
	redir_node->priority = REDIR_P;
	redir_node->exec = redir_exec;
	redir_node->data = strdup(token->data); //Replace this with ft
	return (redir_node);
}
