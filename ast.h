#ifndef AST_H
# define AST_H
# include "tokenizer.h"
# include "num_ast_node.h"
# include "mult_ast_node.h"
# include "plus_ast_node.h"

typedef struct		s_ast
{
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
	int				(*exec)(struct s_ast *self);
	char			data;
	int				priority;
}					t_ast;

t_ast	*build_ast(t_token *t);

#endif
