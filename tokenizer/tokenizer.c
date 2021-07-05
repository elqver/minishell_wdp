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
	new->data = s; //strdup(s);					 // TODO: replace with own
				   // automatonize() calls append_... with strndup,
				   // think about memory management
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

void		free_token_list(t_token *t)
{
	t_token	*tmp;

	while (t != NULL)
	{
		tmp = t;
		t = t->next;
		free(tmp->data); // I wrote it later with no thinking CARE
							// Might be danger if no string saved in token
							// Or if it's achivable in other places
		free(tmp);
	}
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
	static t_state	*(* automata[4])(void) = {redir_automaton, word_automaton,
												pipe_automaton, NULL};
	static int		token_properties[3] = {REDIR_P, ARG_P, PIPE_P};
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
	free_token_list(self->token_list);
	return (-1);
}

int			tokenize_string(t_tokenizer *self, char *s)
{
	int	tmp; // how many chars skiped in automatonize (lexeme_len to be clear)

	free_token_list(self->token_list); // we wrote that with some thinking
										// but it could be useful
	tmp = 1;
	while (*s != '\0')
	{
		if (!isspace(*s))
			tmp = automatonize(self, s);
		if (tmp == -1)
			return (-1);
		s += tmp;
		tmp = 1;
	}
	return (0);
}

t_tokenizer	*new_tokenizer(void)
{
	t_tokenizer	*t;

	t = calloc(sizeof(t_tokenizer), 1);
	t->exec = tokenize_string;
	return (t);
}