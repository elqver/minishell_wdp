#include "tokenizer.h"

static t_token	*new_token(char *s, int priority)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->data = s;
	new->priority = priority;
	new->next = NULL;
	return (new);
}

t_token	*append_token_list(t_token **t, char *s, int priority)
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
