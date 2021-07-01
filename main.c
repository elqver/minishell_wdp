#include "automata/nfa/nfa.h"
#include "tokenizer/tokenizer.h"
#include "ast/ast.h"

int		main(int ac, char **av, char **envp)
{
	t_tokenizer *t;
	t_ast		*ast;

	if (ac == 1)
	{
		printf("No input\n");
		return (1);
	}
	t = new_tokenizer();
	t->exec(t, av[1]);
	//print_token_list(t->token_list);
	ast = build_ast(t->token_list);
	print_ast(ast, 0);
	ast->exec(ast, envp);
	return (0);
}
