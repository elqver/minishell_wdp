#include "builtins.h"
#include "env.h"



static int	arg_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static int	cd_path(char *path)
{
	char	*tmp;

	tmp = find_env_val("OLDPWD");
	append_env_list("OLDPWD", find_env_val("PWD"));
	if (chdir(path) == -1)
	{
		append_env_list("OLDPWD", tmp);
		return (-1);	
	}
	tmp = getcwd(NULL, 0);
	append_env_list("PWD", tmp);
	free(tmp);
	return (1);
}

static int	cd_root(void)
{
	return (cd_path(find_env_val("HOME")));
}

void		cd(char **args)
{
	int	arg_l;

	arg_l = arg_len(args);
	if (arg_l == 1)
	{
		cd_root();
		return ;
	}
	if (arg_l > 2)
	{
		printf("Wrong nuber of arguments\n");
		return ;
	}
	cd_path(args[1]);
}


/*
void	cd(char **args)
{
	char	*tmp;

	tmp = find_env_val("PWD");
	if (!chdir(args[1]))
	{
		printf("WDP: cd: %s: No such file or directory\n", args[1]);
		return ;
	}
	if (find_env_var("OLDPWD"))
		free(find_env_var("OLDPWD")->val);
	append_env_list("OLDPWD", tmp);
	append_env_list("PWD", getcwd(NULL, 0));
}
*/
