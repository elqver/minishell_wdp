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

static void	replace_tilda(char **path)
{
	char	*home_val;

	home_val = getenv("HOME");
	if (home_val == NULL)
		return ;
	replace_substring(path, 0, 1, home_val);
}

static int	cd_path(char *path)
{
	char	*tmp;

	if (path[0] == '~')
		replace_tilda(&path);
	tmp = find_env_val("OLDPWD");
	append_env_list("OLDPWD", find_env_val("PWD"));
	if (chdir(path) == -1)
	{
		printf("%s: No such directory\n", path);
		append_env_list("OLDPWD", tmp);
		return (1);
	}
	tmp = getcwd(NULL, 0);
	append_env_list("PWD", tmp);
	free(tmp);
	return (0);
}

static int	cd_root(void)
{
	char	*home_val;

	home_val = find_env_val("HOME");
	if (home_val)
		return (cd_path(home_val));
	printf("Error: HOME not set\n");
	return (1);
}

int	cd(char **args)
{
	int		arg_l;
	int		res;
	char	*path;

	arg_l = arg_len(args);
	if (arg_l == 1)
		return (cd_root());
	path = ft_strdup(args[1]);
	res = cd_path(path);
	free(path);
	return (res);
}
