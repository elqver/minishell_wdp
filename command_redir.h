#ifndef COMMAND_REDIR_H
# define COMMAND_REDIR_H

# include "ast.h"

# define ONE_LEFT_REDIR 1
# define ONE_RIGHT_REDIR 2
# define TWO_RIGHT_REDIR 3

t_ast	*create_redir_node(t_token *token);

#endif
