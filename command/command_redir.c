#include "command_commands.h"
#include "../tokenizer/tokenizer.h"
#include <ctype.h> //???
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

int	get_type_of_redir(char *redir)
{
	if (strncmp(redir, "<<", 2) == 0)
		return (TWO_LEFT_REDIR);
	if (strncmp(redir, ">>", 2) == 0)
		return (TWO_RIGHT_REDIR);
	if (strncmp(redir, "<", 1) == 0)
		return (ONE_LEFT_REDIR);
	if (strncmp(redir, ">", 1) == 0)
		return (ONE_RIGHT_REDIR);
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

static int	one_right_redir(t_ast *self)
{
	int file_fd;

	file_fd = open(self->left->data, O_WRONLY | O_CREAT, S_IWUSR | S_IXGRP);
	if (file_fd < 0)
		return (1);
	dup2(file_fd, 1);
	close(file_fd);
	return (0);
}

static int	two_right_redir(t_ast *self)
{
	int file_fd;

	file_fd = open(self->left->data, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (file_fd < 0)
		return (1);
	dup2(file_fd, 1);
	close(file_fd);
	return (0);
}

static int	has_quotes(char *line)
{
	while (*line)
	{
		if (single_quote_condition(*line) || double_quote_condition(*line))
			return (1);
		line++;
	}
	return (0);
}

static void	heredoc(char *delimeter, int env_subst_needed, int *fd_here)
{
	char	*line_read;

	line_read = readline("> ");
	while (strcmp(line_read, delimeter)) // TODO: replace later
	{
		if (env_subst_needed)
			handle_envs(&line_read);
		write(fd_here[1], line_read, strlen(line_read)); // TODO: replace later
		write(fd_here[1], "\n", 1); // TODO: replace later
		line_read = readline("> ");
	}
}

static int	two_left_redir(t_ast *self)
{
	char	*delimeter;
	int		env_subst_needed;
	int		fd_redirect[2];

	delimeter = self->left->data;
	env_subst_needed = !has_quotes(delimeter);
	resect_quotes_from_line(&delimeter);
	pipe(fd_redirect);

	heredoc(delimeter, env_subst_needed, fd_redirect);
	close(fd_redirect[1]);
	dup2(fd_redirect[0], 0);

	return (0);
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
	if (redir_type == TWO_LEFT_REDIR)
		two_left_redir(self);
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
