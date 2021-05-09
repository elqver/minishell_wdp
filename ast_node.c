#include "ast_node.h"

t_ast	*create_node_by_token(t_token *t)
{
	if (is_exp(t))
		return (create_exp_node());
	if (is_num(t))
		return (create_num_node(t->data));
	if (is_mult(t))
		return (create_mult_node());
	if (is_plus(t))
		return (create_plus_node());
	if (is_sub(t))
		return (create_sub_node());
	if (is_div(t))
		return (create_div_node());
	return (NULL);
}
