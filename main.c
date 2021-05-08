#include "tokenizer.h"
#include "ast.h"
#include "ast_node.h"

int		main(void)
{
	char s[] = "1 + 3 * 8";
	t_token *t = tokenizer(s);
	print_token_list(t);
	print_ast(build_ast(t));
}
