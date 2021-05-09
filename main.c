#include "tokenizer.h"
#include "ast.h"
#include "ast_node.h"

int		exec_line(char *line)
{
	printf("NEW EXAMPLE: %s\n", line);
	t_token *t = tokenizer(line);
	t_ast *ast = build_ast(t);
	if (ast == NULL)
	{
		printf("Failed growing tree\n");
		return (1);
	}
	print_ast(ast, 0);
	int r = ast->exec(ast);
	printf("Result of calculation: %d\n", r);
	printf("\n\n");
	return (0);
}

int		main(void)
{

	/*
	exec_line("2 ** 3");
	//exec_line("6 / 2 - 2 * 8");
	//exec_line("2 ** 3 * 2");

	//exec_line("1 - 2 ** 3 * 2 / 8");
	
	//exec_line("4 * 2 / 8");
	//exec_line("2 ** 3 * 2 / 8");
	exec_line("1 - 2 ** 3 * 2");
	exec_line("1 - 2 ** 3 * 2 / 8");
	exec_line("1 - 2 ** 3 * 2 * 8");


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
	exec_line("-1 - -1");
	exec_line("2 * 3");
}
