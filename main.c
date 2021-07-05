#include "automata/nfa/nfa.h"
#include "tokenizer/tokenizer.h"
#include "ast/ast.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h> // TODO: replace later

char	*cut_out_substring(char **line, int start, int length)
{
	char	*new_line;
	int		i;
	int		len;

	len = strlen(*line);
	new_line = malloc(len - length + 1); // TODO: take it out
	if (!new_line || start >= len || start + length >= len || start < 0 || length <= 0)
		return (NULL);
	i = -1;
	while (++i < start)
		new_line[i] = (*line)[i];
	i--;
	while (++i < len - length)
		new_line[i] = (*line)[i + length];
	new_line[i] = '\0';

	*line = new_line;
	return (new_line);
}

char	*insert_substring(char **line, int index, char *subs)
{
	char	*new_line;
	int		line_len;
	int		subs_len;
	int		i;

	line_len = strlen(*line);
	subs_len = strlen(subs);
	new_line = malloc(line_len + subs_len + 1);
	i = -1;
	while (++i < index)
		new_line[i] = (*line)[i];
	i--;
	while (++i < index + subs_len)
		new_line[i] = subs[i - index];
	i--;
	while (++i < line_len + subs_len)
		new_line[i] = (*line)[i + subs_len];
	new_line[i] = '\0';
	*line = new_line;
	return (new_line);
}


void	handle_env(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '<<') // YEP!
			while (is_space((*line)[i]))
				i++;
		if ($)
			replace env handle_line(env)
			handle_line();
			return();
		i++;
	}
}

void	handle_line(char **line)
{
	t_tokenizer	*t;
	t_ast		*ast;

	handle_env(line);
	t = new_tokenizer(); // TODO: LEAK HERE
	t->exec(t, *line);
	ast = build_ast(t->token_list);
	ast->exec(ast);
	destroy_ast(ast);
}

void	main_loop(char **envp)
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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);	

	main_loop(envp);
}

