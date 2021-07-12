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
	set_exit_code(WEXITSTATUS(stat_loc));
}

int	wdp_exit(char **args)
{
	(void)args;
	exit(get_exit_code());
}
