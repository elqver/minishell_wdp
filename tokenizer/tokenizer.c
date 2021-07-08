#include "tokenizer.h"

static void	print_token(t_token *t)
{
	printf("Token value:\t%s\n", t->data);
	printf("Token priority:\t%d\n", t->priority);
}

void	print_token_list(t_token *t)
{
	if (t == NULL)
		printf("Token list is empty\n");
	while (t != NULL)
	{
		print_token(t);
		t = t->next;
	}
}

t_token		*new_token(char *s, int priority)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->data = s;
	new->priority = priority;
	new->next = NULL;
	return (new);
}

t_token		*append_token_list(t_token **t, char *s, int priority)
{
	t_token	*ptr;

	if (*t == NULL)
	{
		*t = new_token(s, priority);
		return (*t);
	}
	ptr = *t;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new_token(s, priority);
	return (*t);
}

t_token			*get_last_token(t_token *t)
{
	if (t == NULL)
		return (NULL);
	while (t->next != NULL)
		t = t->next;
	return (t);
}


int			automatonize(t_tokenizer *self, char *s)
{
	static t_state	*(* automata[4])(void) = {word_automaton, redir_automaton,
												pipe_automaton, NULL};
	static int		token_properties[3] = {ARG_P, REDIR_P, PIPE_P};
	t_state			*automaton;
	int				lexeme_len;
	int				i;

	i = -1;
	while (automata[++i] != NULL)
	{
		automaton = automata[i]();
		lexeme_len = get_lexeme_len(automaton, s);
		destroy_regex(automaton);
		if (lexeme_len >= 0)
		{
			append_token_list(&self->token_list, strndup(s, lexeme_len),
								token_properties[i]);
			return (lexeme_len);
		}
	}
	return (-1);
}

int			tokenize_string(t_tokenizer *self, char *s)
{
	int	lexeme_len; // how many chars skiped in automatonize (lexeme_len to be clear)

	lexeme_len = 1;
	while (*s != '\0')
	{
		if (!isspace(*s))
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
	t_token *token;
	t_token *tmp;

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

void	resect_quotes(t_tokenizer *self)
{
	int		i;
	t_token	*token;

	token = self->token_list;
	while (token)
	{
		i = 0;
		while (token->data[i])
		{
			if (token->data[i] == '\'' || token->data[i] == '\"')
				resect_substring(&(token->data), i--, 1);
			i++;
		}
		token = token->next;
	}
} 

int	tokenizer_executor(t_tokenizer *self, char **line)
{
	handle_envs(line);
	tokenize_string(self, *line);
	resect_quotes(self);
	return (0xBEEF);
}

t_tokenizer	*new_tokenizer(void)
{
	t_tokenizer	*t;

	t = calloc(sizeof(t_tokenizer), 1);
	//t->exec = tokenize_string;
	t->exec = tokenizer_executor;
	return (t);
}
