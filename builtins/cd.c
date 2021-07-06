#include "builtins.h"
#include "env.h"

void	cd(char **args)
{
	char	*tmp;

	tmp = NULL;
	if (find_env_var("PWD"))
		tmp = find_env_var("PWD")->val;
	if (!args[1])
	{
		free(args[1]);
		args[1] = strdup("/"); // TODO: replace with own ft_
		cd(args);
		return ;
	}
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
