#include "input.h"

void		append_string(t_string *self, char c)
{
	if (self->i == self->size)
		self->string = realloc(self->string, self->size *= 2);
	self->string[self->i++] = c;
	self->string[self->i] = '\0';
}

char		pop_string(t_string *self)
{
	char	c;

	c = self->string[self->i];
	self->string[self->i--] = '\0';
	return (c);
}

void		del_string(t_string *self)
{
	free(self->string);
	free(self);
}

t_string	*copy_string(t_string *src)
{
	t_string	*new;

	if (src == NULL)
		return (NULL);
	new = new_string();
	new->string = strdup(src->string);
	new->size = src->size;
	new->i = src->i;
	return (new);
}

t_string	*new_string(void)
{
	t_string	*new;

	new = malloc(sizeof(t_string));
	new->size = 10;
	new->string = calloc(sizeof(char), new->size);
	new->i = 0;
	return (new);
}

t_history	*new_history_node(t_string *s)
{
	t_history	*new;

	new = calloc(sizeof(t_history), 1);
	new->data = s;
	return (new);
}

t_history	*push_history(t_history **h, t_string *s)
{
	t_history	*new;

	if (*h == NULL)
	{
		*h = new_history_node(s);
		return (*h);
	}
	new = new_history_node(s);
	new->older = *h;
	(*h)->newer = new;
	*h = new;
	return (new);
}

t_history	*get_newest_entry(t_history *h)
{
	while (h->newer != NULL)
		h = h->newer;
	return (h);
}
