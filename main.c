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

	t = new_tokenizer(); 
	t->exec(t, line);
	ast = build_ast(t->token_list);
	if (ast != NULL)
		ast->exec(ast);
	else
	{
		printf("Error: invalid syntax\n");
		return ;
	}
	destroy_ast(ast);
	destroy_tokenizer(t);
}

static int	*singleton_original_file_descriptors(void)
{
	static int	original_descriptors[2];	

	return (original_descriptors);
}

void	restore_original_file_descriptors(void)
{
	int	*original_descriptors;

	original_descriptors = singleton_original_file_descriptors();
	dup2(original_descriptors[0], 0);
	dup2(original_descriptors[1], 1);
}

static void	save_original_file_descriptors(void)
{
	int	*original_descriptors;

	original_descriptors = singleton_original_file_descriptors();
	original_descriptors[0] = dup(0);
	original_descriptors[1] = dup(1);
}

void	main_loop(void)
{
	char *line;
	
	save_original_file_descriptors();
	line = NULL;
	while (0xDEFEC8ED)
	{
		line = readline("WilliamD $ ");
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		if (strlen(line))
		{
			add_history(line);
			handle_line(&line);
		}
		free(line);
		line = NULL;
		restore_original_file_descriptors();
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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	create_env_list(envp);
	main_loop();
}
