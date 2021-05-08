#include "tokenizer.h"
#include "ast.h"
#include "ast_node.h"

int		exec_line(char *line)
{
	printf("NEW EXAMPLE: %s\n", line);
	t_token *t = tokenizer(line);
	t_ast *ast = build_ast(t);
	print_ast(ast, 0);
	printf("\n\n\n");
	return (0);
}

int		main(void)
{
	/*
	// valid
	exec_line("1 + 3 * 8");
	exec_line("1 + 3 * 8 + 4");
	exec_line("1 * 3 + 8 * 2");
	exec_line("1 * 2 * 3 * 4 * 5 + 6 + 7 + 8");
	exec_line("1 + 2 * 4 * 5");
	exec_line("1 + 2 + 3 + 4 * 5 * 6 * 7 * 8");
	exec_line("1 + 2 * 3 + 4 * 5 + 6");
	exec_line("1 * 2 + 3 * 4 + 5 * 6");
	*/

	//not valid
	exec_line("1 1 1");
	exec_line("+ + +");
	exec_line(" ");
	exec_line("1 + 2 3");
	exec_line("+ 3 - 1");
	exec_line("1 + 2 +");
	exec_line("1 + 2 *");
	exec_line("1 * 2 +");
}
