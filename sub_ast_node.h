#ifndef SUB_AST_NODE_H
# define SUB_AST_NODE_H

# include "tokenizer.h"
# include "ast_struct.h"

int		is_sub(t_token *t);
t_ast	*create_sub_node(void);

#endif
