#include "nfa.h"
#include "tokenizer.h"

int		main(int ac, char **av)
{
	t_tokenizer *t;

	if (ac == 1)
	{
		printf("No input\n");
		return (1);
	}
	t = new_tokenizer();
	t->exec(t, av[1]);
	print_token_list(t->token_list);
	return (0);
}
