#include "builtins/env.h"
#include "parser/automata/nfa.h"
#include "tokenizer/tokenizer.h"
#include "ast/ast.h"
#include "builtins/builtins.h"
#include "signals/signal_modes.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "main_header.h"

void	handle_line(char **line)
{
	t_tokenizer	*t;
	int			print_flag;

	t = new_tokenizer();
	t->exec(t, line);
	build_ast(t->token_list);
	print_flag = get_printing_flags();
	if (print_flag & 2)
		print_token_list(t->token_list);
	if (print_flag & 1)
		print_ast(get_ast());
	destroy_tokenizer(t);
	if (get_ast() == NULL)
	{
		printf("Error: invalid syntax\n");
		set_exit_code(258);
		return ;
	}
	handle_heredocs();
	execute_ast();
	set_ast(NULL);
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
	char	*line;

	save_original_file_descriptors();
	line = NULL;
	while (0xDEFEC8ED)
	{
		switch_to_interactive_mode();
		line = readline("WilliamD $ ");
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		if (ft_strlen(line))
		{
			add_history(line);
			handle_line(&line);
		}
		free(line);
		line = NULL;
		restore_original_file_descriptors();
	}
}
