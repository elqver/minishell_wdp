#ifndef MUL_AST_NODE_H
# define MUL_AST_NODE_H

# include "tokenizer.h"
# include "ast_struct.h"

t_ast	*create_mult_node(void);
int		is_mult(t_token *t);

#endif
