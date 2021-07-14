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
