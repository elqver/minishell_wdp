#include "ast.h"
#include "../command/command_commands.h"

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

static void	execute_heredoc(char *delimeter,
		int env_subst_needed, int fd_to_write)
{
	char	*line_read;

	line_read = readline("> ");
	if (!line_read)
		return ;
	while (strcmp(line_read, delimeter) && get_ast()) // TODO: replace later
	{
		if (!line_read)
			return ;
		if (env_subst_needed)
			handle_envs(&line_read);
		write(fd_to_write, line_read, strlen(line_read)); // TODO: replace later
		write(fd_to_write, "\n", 1); // TODO: replace later
		free(line_read);
		line_read = readline("> ");
	}
	free(line_read);
}

static void	handle_heredoc_node_parent(t_ast *self,
		pid_t childs_pid, int *fd_redirect)
{
	close(fd_redirect[1]);
	waitpid_logging(childs_pid);
	if (get_exit_code() == 1)
	{
		close(fd_redirect[0]);
		set_ast(NULL);
		return ;
	}
	free(self->left->data);
	self->left->data = malloc(3);
	sprintf(self->left->data, "%d", fd_redirect[0]); // TODO: sgaslfgkjasdlfkjasldkfj
}

static void	handle_heredoc_node_child(t_ast *self, int fd_to_write)
{
	char	*delimeter;
	int		env_subst_needed;

	switch_to_heredoc_mode();
	delimeter = self->left->data;
	env_subst_needed = !has_quotes(delimeter);
	resect_quotes_from_line(&delimeter);
	execute_heredoc(delimeter, env_subst_needed, fd_to_write);
	exit(0);
}

void	handle_heredoc_node(t_ast *self)
{
	int		fd_redirect[2];
	pid_t	pid;

	restore_original_file_descriptors();
	pipe(fd_redirect);
	pid = fork();
	if (pid == 0)
		handle_heredoc_node_child(self, fd_redirect[1]);
	else
		handle_heredoc_node_parent(self, pid, fd_redirect);
}
