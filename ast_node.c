#include "ast_node.h"

t_ast	*create_node_by_token(t_token *t)
{
	if (is_num(t))
		return (create_num_node(t->data[0]));
	if (is_mult(t))
		return (create_mult_node());
	if (is_plus(t))
		return (create_plus_node());
	return (NULL);
}
