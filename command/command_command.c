#include "command_commands.h"
#include "../builtins/builtins.h"

int		is_executable_in_dir(char *executable, char *dir)
{
	DIR				*dirp;
	struct dirent	*dp;
	size_t			len;

   dirp = opendir(dir);
   if (dirp == NULL)
	   return (0);
   len = strlen(executable);
   while ((dp = readdir(dirp)) != NULL)
   {
	   if (dp->d_namlen == len && strcmp(dp->d_name, executable) == 0)
	   {
		   (void)closedir(dirp);
		   return (1);
	   }
   }
   (void)closedir(dirp);
   return (0);
}

int		execute_command_from_path(char **av)
{
	char		**paths_arr;
	char		*path;
	unsigned	i;
	pid_t		pid;

	paths_arr = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths_arr[i] != NULL)
	{
		if (is_executable_in_dir(av[0], paths_arr[i]) == 1)
		{
			path = ft_strjoin(paths_arr[i], "/");
			path = ft_strjoin(path, av[0]);		// LEAKS !!!!!!!!!!!!!!
			pid = fork();
			if (pid == 0)
			{
				execve(path, av, array_from_list(*env_list(get)));
				exit(1);
			}
			waitpid(pid, NULL, 0);
			return (0);
		}
		i++;
	}
	return (1); // error
}

int			calculate_args_arr_length(t_ast *self)
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

char		**generate_args_arr(t_ast *self)
{
	char 	**argv;
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

void	delete_args_arr(char **args)
{
	unsigned int	i;

	i = 0;
	while (args[i] != NULL)
		free(args[i++]);
	free(args);
}

int			execute_command(t_ast *self)
{
	char		**args;
	static char *builtins_names[8] = {"echo", "cd", "pwd", \
		"export", "unset", "env", "exit", NULL};
	static void	(*builtins[8])(char **) = {echo, cd, pwd, env_export, unset, env, wdp_exit, NULL};
	int			i;

	i = 0;
	args = generate_args_arr(self);
	while (builtins[i] != NULL)
	{
		if (strcmp(self->data, builtins_names[i]) == 0)
		{
			builtins[i](args);
			delete_args_arr(args);
			return (69);
		}
		i++;
	}
	return (execute_command_from_path(args));
	return (1);
}

t_ast		*create_command_node(t_token *token)
{
	t_ast	*command_node;

	command_node = calloc(sizeof(t_ast), 1);
	command_node->priority = 1;
	command_node->exec = execute_command;
	command_node->data = strdup(token->data); //Replace this with ft
	command_node->priority = ARG_P;
	return (command_node);
}
