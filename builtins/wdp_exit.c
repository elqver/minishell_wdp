#include "builtins.h"

static int	exit_code_singleton(int *new_code)
{
	static int	exit_code;

	if (new_code != NULL)
		exit_code = *new_code;
	return (exit_code);
}

int	get_exit_code(void)
{
	return (exit_code_singleton(NULL));
}

void	set_exit_code(int new_code)
{
	exit_code_singleton(&new_code);
}

void	waitpid_logging(pid_t pid)
{
	int	stat_loc;

	waitpid(pid, &stat_loc, 0);
	if (WIFEXITED(stat_loc))
		set_exit_code(WEXITSTATUS(stat_loc));
	if (WIFSIGNALED(stat_loc))
		set_exit_code(WTERMSIG(stat_loc) + 128);
}

int	wdp_exit(char **args)
{
	(void)args;
	exit(get_exit_code());
}
