#include "command_commands.h"
#include "../builtins/builtins.h"

int	contains_slash(char *path_to_binary)
{
	int	i;

	i = 0;
	while (path_to_binary[i] != '\0')
	{
		if (path_to_binary[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	execute_binary_file(char *path, char **av)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(path, av, array_from_list(get_env_list()));
		delete_args_arr(av);
		exit(126);
	}
	delete_args_arr(av);
	waitpid_logging(pid);
	return (0);
}
