#include "tokenizer.h"
#include "../builtins/env.h"

#include <ctype.h> // TODO: delete

char	*resect_substring(char **line, int start, int length)
{
	char	*new_line;
	int		i;
	int		len;

	len = strlen(*line);
	new_line = malloc(len - length + 1); // TODO: take it out
	if (!new_line || start >= len || start + length > len || start < 0 || length <= 0)
		return (NULL);
	i = -1;
	while (++i < start)
		new_line[i] = (*line)[i];
	i--;
	while (++i < len - length)
		new_line[i] = (*line)[i + length];
	new_line[i] = '\0';
	free(*line);
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
		new_line[i] = (*line)[i - subs_len];
	new_line[i] = '\0';
	free(*line);
	*line = new_line;
	return (new_line);
}

static void	replace_substring(char **line, int index, int len, char *replacement)
{
	resect_substring(line, index, len);
	if (replacement == NULL)
		return ;
	insert_substring(line, index, replacement);
}

static t_state	*env_automaton(void)
{
	t_state	*s1;
	t_state	*s2;
	t_state	*s3;

	s3 = new_state(1, 0, NULL);
	append_transition(&s3->transition_list,
			letter_digit_underscore_condition, s3);
	s2 = new_state(0, 0, new_transition(
				letter_underscore_condition, s3));
	s1 = new_state(0, 1, new_transition(dollar_condition, s2));
	return (s1);
}

static void	handle_env(char **line, int i)
{
	static t_state	*automaton;
	char			*env;
	int				lexeme_len;

	if (automaton == NULL)
		automaton = env_automaton();
	lexeme_len = get_lexeme_len(automaton, *line + i);
	if (lexeme_len == -1)
		return ;
	env = strndup(*line + i + 1, lexeme_len - 1);
	replace_substring(line, i, lexeme_len, find_env_val(env));
	free(env);
}

static int	skip_single_quotes(char *line, unsigned int *i)
{
	static t_state	*automaton;
	int				lexeme_len;

	if (automaton == NULL)
		automaton = single_quote_automaton();
	lexeme_len = get_lexeme_len(automaton, line + *i);
	if (lexeme_len == -1)
		return (-1);
	*i += lexeme_len;
	return (0);
}

static int	skip_heredoc(char *line, unsigned int *i)
{
	static t_state	*automaton;
	int				lexeme_len;

	if (automaton == NULL)
		automaton = heredoc_automaton();
	lexeme_len = get_lexeme_len(automaton, line + *i);
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
		if ((*line)[i] == '<' && (*line)[i + 1] == '<' && skip_heredoc(*line, &i) == -1)
			return (-1);
		handle_env(line, i);
		i++;
	}
	return (0);
}
