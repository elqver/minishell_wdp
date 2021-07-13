#include "builtins/env.h"
#include "automata/nfa/nfa.h"
#include "tokenizer/tokenizer.h"
#include "ast/ast.h"
#include "builtins/builtins.h"
#include "signals/modes.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h> // TODO: replace later

void	handle_line(char **line)
{
	t_tokenizer	*t;

	t = new_tokenizer(); 
	t->exec(t, line);
	build_ast(t->token_list);
	destroy_tokenizer(t);
	if (get_ast() == NULL)
	{
		printf("Error: invalid syntax\n");
		set_exit_code(258);
		return ;
	}
	handle_heredocs();
	execute_abstract_syntax_tree();
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
		if (strlen(line)) // TODO: replace with ft_
		{
			add_history(line);
			handle_line(&line);
		}
		free(line);
		line = NULL;
		restore_original_file_descriptors();
	}
}

static void	increment_shlvl(void)
{
	t_env	*env;
	int		delete_this_shit;
	
	env = find_env_var("SHLVL");
	if (env == NULL)
	{
		append_env_list("SHLVL", strdup("1"));
		return ;
	}
	delete_this_shit = atoi(env->val) + 1;
	free(env->val);
	env->val = calloc(sizeof(char), 20);
	// TODO:
	// TODO: replace all this with normal code
	// TODO:
	// TODO:
	sprintf(env->val, "%d", delete_this_shit);
}

// TODO: ; && backslash

int		main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	create_env_list(envp);
	increment_shlvl();
	main_loop();
}
