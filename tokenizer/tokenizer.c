#include "tokenizer.h"

int	automatonize(t_tokenizer *self, char *s)
{
	static	t_state	*(*automata[4])(void) = {word_automaton,
		redir_automaton, pipe_automaton, NULL};
	static int		token_properties[3] = {ARG_P, REDIR_P, PIPE_P};
	t_state			*automaton;
	int				lexeme_len;
	int				i;

	i = -1;
	while (automata[++i] != NULL)
	{
		automaton = automata[i]();
		lexeme_len = get_lexeme_len(automaton, s);
		if (lexeme_len >= 0)
		{
			append_token_list(&self->token_list, ft_strndup(s, lexeme_len),
				token_properties[i]);
			return (lexeme_len);
		}
	}
	return (-1);
}

int	tokenize_string(t_tokenizer *self, char *s)
{
	int	lexeme_len;

	lexeme_len = 1;
	while (*s != '\0')
	{
		if (!ft_isspace(*s))
			lexeme_len = automatonize(self, s);
		if (lexeme_len == -1)
			return (-1);
		s += lexeme_len;
		lexeme_len = 1;
	}
	return (0);
}

void	destroy_tokenizer(t_tokenizer *self)
{
	t_token	*token;
	t_token	*tmp;

	token = self->token_list;
	while (token != NULL)
	{
		tmp = token->next;
		free(token->data);
		free(token);
		token = tmp;
	}
	free(self);
}

int	tokenizer_exec(t_tokenizer *self, char **line)
{
	handle_envs(line);
	tokenize_string(self, *line);
	resect_quotes(self);
	return (0xBEEF);
}

t_tokenizer	*new_tokenizer(void)
{
	t_tokenizer	*t;

	t = ft_calloc(sizeof(t_tokenizer), 1);
	t->exec = tokenizer_exec;
	return (t);
}
