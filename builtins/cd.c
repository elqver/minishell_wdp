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
	printf("| %s |\n", path);
	if (chdir(path) == -1)
	{
		append_env_list("OLDPWD", tmp);
		return (1);
	}
	tmp = getcwd(NULL, 0);
	append_env_list("PWD", tmp);
	free(tmp);
	return (0);
}

static int	cd_root(void) // TODO: protect for unset $HOME is it actually working?
{
	return (cd_path(find_env_val("HOME")));
}

// TODO: if ~ is an argument for cd need to ask OS for $HOME value in runtime
int	cd(char **args)
{
	int	arg_l;

	arg_l = arg_len(args);
	if (arg_l == 1)
		return (cd_root());
	return (cd_path(args[1]));
}
