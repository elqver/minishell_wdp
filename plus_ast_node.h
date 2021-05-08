#ifndef PLUS_AST_NODE_H
# define PLUS_AST_NODE_H

# include "tokenizer.h"
# include "ast_struct.h"

int			is_plus(t_token *t);
t_ast		*create_plus_node(void);

#endif
