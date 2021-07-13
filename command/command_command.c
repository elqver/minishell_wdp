#include "command_commands.h"
#include "../builtins/builtins.h"

void	delete_args_arr(char **args)
{
	unsigned int	i;

	i = 0;
	while (args[i] != NULL)
		free(args[i++]);
	free(args);
}

int	is_executable_in_dir(char *executable, char *dir)
{
	DIR				*dirp;
	struct dirent	*dp;
	size_t			len;

	dirp = opendir(dir);
	if (dirp == NULL)
		return (0);
	len = strlen(executable);
	dp = readdir(dirp);
	while (dp != NULL)
	{
		if (dp->d_namlen == len && strcmp(dp->d_name, executable) == 0) // TODO: replace with ft_
		{
			(void)closedir(dirp);
			return (1);
		}
		dp = readdir(dirp);
	}
	(void)closedir(dirp);
	return (0);
}

int	execute_command_in_dir(char **av, char *command_directory)
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
		execve(path, av, array_from_list(*env_list(get)));
		exit(126);
	}
	free(path);
	waitpid_logging(pid);
	return (0);
}

int	execute_command_from_path(char **av)
{
	char			**paths_arr;
	int				res;
	unsigned int	i;

	// TODO: test with unset PATH
	paths_arr = ft_split(find_env_val("PATH"), ':');
	i = 0;
	while (paths_arr[i] != NULL)
	{
		if (is_executable_in_dir(av[0], paths_arr[i]) == 1)
		{
			res = execute_command_in_dir(av, paths_arr[i]);
			delete_args_arr(paths_arr);
			return (res);
		}
		i++;
	}
	set_exit_code(127);
	delete_args_arr(paths_arr);
	return (1); // error
}

int	calculate_args_arr_length(t_ast *self)
{
	int	length;

	length = 0;
	while (self != NULL)
	{
		length++;
		self = self->right;
	}
	return (length);
}

char	**generate_args_arr(t_ast *self)
{
	char	**argv;
	int		argc;
	int		i;

	argc = calculate_args_arr_length(self);
	argv = calloc(sizeof(char *), argc + 1);
	i = 0;
	while (i < argc)
	{
		argv[i] = strdup(self->data);
		self = self->right;
		i++;
	}
	return (argv);
}

static int	contains_slash(char *path_to_binary)
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

static int	execute_binary_file(char *path, char **av)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(path, av, array_from_list(*env_list(get)));
		delete_args_arr(av);
		exit(126);
	}
	delete_args_arr(av);
	waitpid_logging(pid);
	return (0);
}

int	execute_command(t_ast *self)
{
	char		**args;
	static char	*builtins_names[8] = {"echo", "cd", "pwd", \
		"export", "unset", "env", "exit", NULL};
	static	int	(*builtins[8])(char **) = {echo, cd, pwd, env_export,
		unset, env, wdp_exit, NULL};
	int			i;
	int			res;

	if (self == NULL)
	{
		set_exit_code(0);
		return (0);
	}
	i = 0;
	args = generate_args_arr(self);
	if (contains_slash(args[0]))
		return (execute_binary_file(args[0], args));
	while (builtins[i] != NULL)
	{
		if (strcmp(self->data, builtins_names[i]) == 0)
		{
			set_exit_code(builtins[i](args));
			delete_args_arr(args);
			return (1);
		}
		i++;
	}
	res = execute_command_from_path(args);
	if (res)
		printf("Command not found\n");
	delete_args_arr(args);
	return (res);
}

t_ast	*create_command_node(t_token *token)
{
	t_ast	*command_node;

	command_node = calloc(sizeof(t_ast), 1);
	command_node->priority = 1;
	command_node->exec = execute_command;
	command_node->data = strdup(token->data); //Replace this with ft
	command_node->priority = ARG_P;
	return (command_node);
}
