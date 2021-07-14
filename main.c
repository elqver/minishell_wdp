#include "builtins/env.h"
#include "parser/automata/nfa.h"
#include "tokenizer/tokenizer.h"
#include "ast/ast.h"
#include "builtins/builtins.h"
#include "signals/signal_modes.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "main_header.h"

static void	increment_shlvl(void)
{
	t_env	*env;
	int		next_shlvl;

	env = find_env_var("SHLVL");
	if (env == NULL)
	{
		append_env_list("SHLVL", ft_strdup("1"));
		return ;
	}
	next_shlvl = ft_atoi(env->val) + 1;
	free(env->val);
	env->val = ft_itoa(next_shlvl);
}

static int	handle_argv(int argc, char **argv)
{
	if (argc == 1)
		return (0);
	if (argc > 3)
		print_help_message();
	if (ft_strcmp(argv[1], "--help") == 0)
		print_help_message();
	if (ft_strcmp(argv[1], "--show") == 0)
	{
		if (argc != 3)
			print_help_message();
		if (ft_strcmp(argv[2], "ast") == 0)
			return (set_printing_flags(1));
		else if (ft_strcmp(argv[2], "tokens") == 0)
			return (set_printing_flags(2));
		else if (ft_strcmp(argv[2], "all") == 0)
			return (set_printing_flags(3));
	}
	print_help_message();
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	handle_argv(argc, argv);
	create_env_list(envp);
	increment_shlvl();
	main_loop();
}
