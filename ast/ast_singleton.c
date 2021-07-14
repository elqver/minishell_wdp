#include "ast.h"

static t_ast	*ast_singleton(t_ast *new_ptr, int change_required)
{
	static t_ast	*saved_ptr;

	if (change_required)
	{
		destroy_ast(saved_ptr);
		saved_ptr = new_ptr;
	}
	return (saved_ptr);
}

t_ast	*get_ast(void)
{
	return (ast_singleton(NULL, 0));
}

t_ast	*set_ast(t_ast *new_ptr)
{
	return (ast_singleton(new_ptr, 1));
}
