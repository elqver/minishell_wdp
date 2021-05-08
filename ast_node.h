#ifndef AST_NODE_H
# define AST_NODE_H

# include "tokenizer.h"
# include "ast_struct.h"
# include "num_ast_node.h"
# include "mul_ast_node.h"
# include "plus_ast_node.h"

t_ast	*create_node_by_token(t_token *t);

#endif
