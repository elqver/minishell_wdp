#ifndef AST_STRUCT_H
# define AST_STRUCT_H

typedef struct		s_ast
{
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
	int				(*exec)(struct s_ast *self);
	char			*data;
	int				priority;
}					t_ast;


#endif
