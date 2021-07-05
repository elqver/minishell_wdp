#ifndef AST_H
# define AST_H

# include <stdlib.h>
# include <stdio.h>
# include "../tokenizer/tokenizer.h"

typedef struct			s_ast
{
	struct s_ast		*left;
	struct s_ast		*right;
	char				*data;
	int					priority;
	int					type;
	int					(* exec)(struct s_ast *self);
}						t_ast;

t_ast	*build_ast(t_token *token);
void	*destroy_ast(t_ast *ast);
void	print_ast(t_ast *a, int pref_len);

#endif 
