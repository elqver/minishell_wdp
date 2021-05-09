#ifndef AST_H
# define AST_H

# include "tokenizer.h"
# include "ast_node.h"
# include "num_ast_node.h"
# include "mul_ast_node.h"
# include "plus_ast_node.h"

# define RED "\033[0;31m"
# define YEL "\033[0;33m"
# define GRE "\033[0;32m"
# define WHI "\033[0;37m"

t_ast	*build_ast(t_token *t);
void	print_ast(t_ast *root, int pref_len);

#endif
