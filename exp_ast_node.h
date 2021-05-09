#ifndef EXP_AST_NODE_H
# define EXP_AST_NODE_H

# include "tokenizer.h"
# include "ast_node.h"
# include <math.h>

int		is_exp(t_token *t);
t_ast	*create_exp_node(void);

#endif
