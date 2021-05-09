#ifndef DIV_AST_NODE_H
# define DIV_AST_NODE_H

# include "tokenizer.h"
# include "ast_struct.h"

int		is_div(t_token *t);
t_ast	*create_div_node(void);

#endif
