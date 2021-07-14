#include "builtins/env.h"
#include "parser/automata/nfa.h"
#include "tokenizer/tokenizer.h"
#include "ast/ast.h"
#include "builtins/builtins.h"
#include "signals/signal_modes.h"
#include <readline/readline.h>
#include <readline/history.h>

void	main_loop(void);

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

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	create_env_list(envp);
	increment_shlvl();
	main_loop();
}
