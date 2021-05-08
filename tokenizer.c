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

t_token		*tokenizer(char *s)
{
	t_token *lst = NULL;
	char	a[2];

	while (*s)
	{
		while (isspace(*s))
			s++;
		a[0] = *s;
		a[1] = 0;
		append(&lst, a);
		s++;
	}
	return (lst);
}

void		print_token_list(t_token *t)
{
	if (t == NULL)
	{
		printf("Null pointer passed\n");
		return ;
	}
	while (t != NULL)
	{
		printf("%s\n", t->data);
		t = t->next;
	}
}
