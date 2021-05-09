#ifndef NUM_AST_NODE_H
# define NUM_AST_NODE_H

# include "tokenizer.h"
# include "ast_struct.h"

t_ast		*create_num_node(char *data);
int			is_num(t_token *t);

#endif
