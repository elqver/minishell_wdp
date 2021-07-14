#include "command_commands.h"
#include "../builtins/builtins.h"
#include "../utils/utils.h"

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
	i = 0;
	while (builtin_names[i] != NULL && ft_strcmp(self->data, builtin_names[i]))
		i++;
	if (builtin_names[i] != NULL)
		set_exit_code(builtins[i](args));
	else if (execute_command_from_path(args) != 0)
		printf("%s: command not found\n", args[0]);
	return (delete_args_arr(args));
}
