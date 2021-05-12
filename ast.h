#ifndef AST_H
# define AST_H

typedef struct			s_child_list
{
	struct s_child_list	*next;
	struct s_ast		*child;
}						t_child_list; 

typedef struct			s_ast
{
	struct s_ast		*parent;
	t_child_list		*child_list;
	int					priority;
	int					(* execute)(struct s_ast *self);
}						t_ast;

#endif 
