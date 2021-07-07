#include "builtins/env.h"
#include "automata/nfa/nfa.h"
#include "tokenizer/tokenizer.h"
#include "ast/ast.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h> // TODO: replace later

void	rl_replace_line(char *a, int b);

void	handle_line(char **line)
{
	t_tokenizer	*t;
	t_ast		*ast;

	t = new_tokenizer(); // TODO: LEAK HERE
	t->exec(t, line);
	print_token_list(t->token_list);
	ast = build_ast(t->token_list);
	ast->exec(ast);
	destroy_ast(ast);
	destroy_tokenizer(t);
	//print_ast(ast, 0);
}

void	main_loop(void)
{
	char *line;
	
	while (0xDEFEC8ED)
	{
		line = readline("WilliamD $ ");
		if (strlen(line))
		{
			add_history(line);
			handle_line(&line);
		}
		free(line);
	}
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	create_env_list(envp);
	main_loop();
}

