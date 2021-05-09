#include "tokenizer.h"

static t_token		*new_node(char *data)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->data = strdup(data);
	new->next = NULL;
	return (new);
}


static t_token		*append(t_token **root, char *data)
{
	t_token	*ptr;

	if (root == NULL)
		return (NULL);
	if (*root == NULL)
	{
		*root = new_node(data);
		return (*root);
	}
	ptr = *root;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new_node(data);
	return (*root);
}

void				num_state_change(t_tokenizer *t, char **number, size_t *size, size_t *i)
{
	*number = realloc(*number, *i + 1);
	(*number)[*i] = '\0';
	append(&t->lst, *number);
	free(*number);
	*number = NULL; 
	*size = 0;
	*i = 0;
}

int					change_state(t_tokenizer *t, int (*new_state)(t_tokenizer *, char), char c)
{
	t->state = new_state;
	t->state(t, c);
	return (0);
}

int					op_state(t_tokenizer *t, char c)
{
	static char		s[3];
	static size_t	i;

	if (i == 0 || (i == 1 && s[0] == '*' && c == '*'))
	{
		s[i++] = c;
		return (0);
	}
	append(&t->lst, s);
	bzero(s, 2);
	i = 0;
	if (isdigit(c))
		return (change_state(t, num_state, c));
	if (isspace(c))	
		return (change_state(t, space_state, c));
	return (1);
}

int					space_state(t_tokenizer *t, char c)
{
	if (isspace(c))
		return (0);
	if (isdigit(c))
		return (change_state(t, num_state, c));
	if (strchr("+-*/", c))
		return (change_state(t, op_state, c));
	return (1);
}

int					num_state(t_tokenizer *t, char c)
{
	static char		*number;
	static size_t	size;
	static size_t	i;

	if (!isdigit(c))
	{
		num_state_change(t, &number, &size, &i);
		if (isspace(c)) 
			return (change_state(t, space_state, c));
		if (strchr("+-*/", c))
			return (change_state(t, op_state, c));
		printf("Error in num_state()\n");
		return (1);
	}
	if (number == NULL)
	{
		size = 10;
		number = malloc(size);
		i = 0;
	}
	if (i == size)
	{
		size *= 2;
		number = realloc(number, size + 1);
	}
	number[i++] = c;
	number[i] = '\0';
	return (0);
}

t_tokenizer			*create_tokenizer(void)
{
	t_tokenizer		*t;

	t = malloc(sizeof(t_tokenizer));
	t->lst = NULL;
	t->state = num_state;
	return (t);
}

t_token				*tokenizer(char *s)
{
	t_tokenizer	tokenizer;

	tokenizer.state = num_state;
	tokenizer.lst = NULL;
	while (*s)
	{
		if (tokenizer.state(&tokenizer, *s) == 1)
		{
			printf("Error in tokenizer cycle\n");
			return (NULL);
		}
		s++;
	}
	tokenizer.state(&tokenizer, ' ');
	return (tokenizer.lst);
}
