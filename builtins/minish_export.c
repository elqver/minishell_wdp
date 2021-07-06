#include "env.h"

t_ast	*minish_export(t_ast *node)
{
	if (node->right == NULL)
		return (declare_x());
	node = node->right;
	while (node != NULL)
	{
		split_append_env(node->data);
		// if (...error...)
		// 	return (NULL)
		node = node->right;
	}
	return (node);
}
