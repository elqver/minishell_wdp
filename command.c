#include "command.h"

static int	get_fd_of_redirection(char **redir)
{
	int	fd;


	if (!isdigit(**redir))
		return (1);
	fd = 0;
	while (isdigit(**redir)) //replace with allowd function later
	{
		fd *= 10;
		fd += **redir - '0';
		(*redir)++;
	}
	return fd;
}


static int	redirect(char *file, int flags, int fd)
{
	int		fd_tmp;

	fd_tmp = open(file, flags);
	if (fd_tmp == -1)
		return (1);
	if (dup2(fd, fd_tmp) == -1)
	{
		close(fd_tmp);
		return (1);
	}
	close(fd_tmp);
	return (0);
}

static int	handle_redirection(char *redir, char *file)
{
	int		fd_number;
	int		flags;

	if (!strcmp(redir, "<"))
		return (redirect(file, O_RDONLY, 0));
	fd_number = get_fd_of_redirection(&redir);
	if (!strcmp(redir, ">>"))
		return (redirect(file, O_WRONLY | O_CREAT | O_APPEND, fd_number));
	if (!strcmp(redir, ">"))
		return (redirect(file, O_WRONLY | O_CREAT, fd_number));
	return (1);
}

static int	handle_redirections(t_child_list *child_list)
{
	while (child_list != NULL)
	{
		if (child_list->child->type == REDIR)
		{
			handle_redirection(child_list->child->data,
								child_list->next->child->data);
			child_list = child_list->next;
		}
		child_list = child_list->next;
	}
	return (0);
}

static char	**create_command_arglist(t_child_list *child_list)
{
	char	**res;
	
}

int			exec_command(t_ast *command)
{
	//redirect everything
	if (handle_redirections(command->child_list))
		return (1);
	//create command arglist
	//run command if it's buildin
	//run command if it's in path
	//return error other way
	
	return (1);
}
