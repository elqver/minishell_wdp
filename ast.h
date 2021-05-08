#ifndef AST_H
# define AST_H

# include "tokenizer.h"
# include "ast_node.h"
# include "num_ast_node.h"
# include "mul_ast_node.h"
# include "plus_ast_node.h"

t_ast	*build_ast(t_token *t);
void	print_ast(t_ast *root, int pref_len);

#endif
