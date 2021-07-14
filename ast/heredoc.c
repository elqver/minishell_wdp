#include "ast.h"
#include "../command/command_commands.h"

static void	recursive_handle_heredocs(t_ast	*self)
{
	if (self == NULL)
		return ;
	if (self->right != NULL)
		recursive_handle_heredocs(self->right);
	if (self->left != NULL)
		recursive_handle_heredocs(self->left);
	if (ft_strncmp(self->data, "<<", 2) == 0) 
		handle_heredoc_node(self);
}

void	handle_heredocs(void)
{
	recursive_handle_heredocs(get_ast());
}
