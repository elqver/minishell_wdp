#include "command_commands.h"
#include "../builtins/builtins.h"
#include "../utils/utils.h"

<<<<<<< HEAD
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
	len = ft_strlen(executable);
	dp = readdir(dirp);
	while (dp != NULL)
	{
		if (dp->d_namlen == len && ft_strcmp(dp->d_name, executable) == 0) // TODO: replace with ft_
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
	if (find_env_var("PATH") == NULL)
	{
		set_exit_code(127);
		return (1);
	}
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
	argv = ft_calloc(sizeof(char *), argc + 1);
	i = 0;
	while (i < argc)
	{
		argv[i] = ft_strdup(self->data);
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

=======
>>>>>>> f4960ae9bbf3e6b6db9c0ed6dede2deeb0034ed3
int	execute_command(t_ast *self)
{
	char		**args;
	static char	*builtin_names[8] = {"echo", "cd", "pwd", \
		"export", "unset", "env", "exit", NULL};
	static	int	(*builtins[8])(char **) = {echo, cd, pwd, env_export,
		unset, env, wdp_exit, NULL};
	int			i;

	if (self == NULL)
		return (set_exit_code(0));
	args = generate_args_arr(self);
	if (contains_slash(args[0]))
		return (execute_binary_file(args[0], args));
<<<<<<< HEAD
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(self->data, builtins_names[i]) == 0)
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

	command_node = ft_calloc(sizeof(t_ast), 1);
	command_node->priority = 1;
	command_node->exec = execute_command;
	command_node->data = ft_strdup(token->data); //Replace this with ft
	command_node->priority = ARG_P;
	return (command_node);
=======
	i = 0;
	while (builtin_names[i] != NULL && strcmp(self->data, builtin_names[i])) // TODO: replace with ft_
		i++;
	if (builtin_names[i] != NULL)
		set_exit_code(builtins[i](args));
	else if (execute_command_from_path(args) != 0)
		printf("%s: command not found\n", args[0]);
	return (delete_args_arr(args));
>>>>>>> f4960ae9bbf3e6b6db9c0ed6dede2deeb0034ed3
}
