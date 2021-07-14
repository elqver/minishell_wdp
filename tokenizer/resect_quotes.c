#include "tokenizer.h"

void	resect_quotes_from_line(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'' || (*line)[i] == '\"')
			resect_substring(line, i--, 1);
		i++;
	}
}

void	resect_quotes(t_tokenizer *self)
{
	int		is_prev_heredoc;
	t_token	*token;

	is_prev_heredoc = 0;
	token = self->token_list;
	while (token)
	{
		if (!is_prev_heredoc)
			resect_quotes_from_line(&(token->data));
		is_prev_heredoc = !strncmp("<<", token->data, 2);
		token = token->next;
	}
}
