#include "nfa.h"
#include "tokenizer.h"
#include "ast.h"

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
	print_ast(build_ast(t->token_list), 0);
	return (0);
}
