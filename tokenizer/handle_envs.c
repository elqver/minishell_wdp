#include "tokenizer.h"
#include "../builtins/env.h"
#include "../builtins/builtins.h"

static char	*get_exit_code_string(void)
{
	static char	*exit_code_string;

	exit_code_string = ft_itoa(get_exit_code());
	return (exit_code_string);
}

static void	handle_env(char **line, int i)
{
	char	*env;
	int		lexeme_len;

	if (ft_strncmp(*line + i, "$?", 2) == 0)
	{
		replace_substring(line, i, 2, get_exit_code_string());
		return ;
	}
	lexeme_len = get_lexeme_len(dollar_env_automaton(), *line + i);
	if (lexeme_len == -1)
		return ;
	env = ft_strndup(*line + i + 1, lexeme_len - 1);
	replace_substring(line, i, lexeme_len, find_env_val(env));
	free(env);
}

static int	skip_single_quotes(char *line, unsigned int *i)
{
	int	lexeme_len;

	lexeme_len = get_lexeme_len(single_quote_automaton(), line + *i);
	if (lexeme_len == -1)
		return (-1);
	*i += lexeme_len;
	return (0);
}

static int	skip_heredoc(char *line, unsigned int *i)
{
	int	lexeme_len;

	lexeme_len = get_lexeme_len(heredoc_automaton(), line + *i);
	if (lexeme_len == -1)
		return (-1);
	*i += lexeme_len;
	return (0);
}

int	handle_envs(char **line)
{
	unsigned int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'' && skip_single_quotes(*line, &i) == -1)
			return (-1);
		if ((*line)[i] == '<' && (*line)[i + 1] == '<' &&
				skip_heredoc(*line, &i) == -1)
			return (-1);
		handle_env(line, i);
		i++;
	}
	return (0);
}
