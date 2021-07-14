#include "command_commands.h"
#include "../builtins/builtins.h"

static int	is_executable_in_dir(char *executable, char *dir)
{
	DIR				*dirp;
	struct dirent	*dp;
	size_t			len;

	dirp = opendir(dir);
	if (dirp == NULL)
		return (0);
	len = ft_strlen(executable);
	dp = readdir(dirp);
	while (dp != NULL)
	{
		if (dp->d_namlen == len && ft_strcmp(dp->d_name, executable) == 0)
		{
			(void)closedir(dirp);
			return (1);
		}
		dp = readdir(dirp);
	}
	(void)closedir(dirp);
	return (0);
}

static int	execute_command_in_dir(char **av, char *command_directory)
{
	char	*path;
	char	*tmp;
	pid_t	pid;

	tmp = ft_strjoin(command_directory, "/");
	path = ft_strjoin(tmp, av[0]);
	free(tmp);
	pid = fork();
	if (pid == 0)
	{
		execve(path, av, array_from_list(get_env_list()));
		exit(126);
	}
	free(path);
	waitpid_logging(pid);
	return (0);
}

int	execute_command_from_path(char **av)
{
	char			**paths_arr;
	unsigned int	i;

	if (find_env_var("PATH") == NULL)
	{
		set_exit_code(127);
		return (1);
	}
	paths_arr = ft_split(find_env_val("PATH"), ':');
	i = 0;
	while (paths_arr[i] != NULL && \
			is_executable_in_dir(av[0], paths_arr[i]) == 0)
		i++;
	if (paths_arr[i] != NULL)
		execute_command_in_dir(av, paths_arr[i]);
	else
		set_exit_code(127);
	delete_args_arr(paths_arr);
	return (paths_arr[i] == NULL);
}
