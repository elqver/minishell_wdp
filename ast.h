#ifndef AST_H
# define AST_H

# include <stdlib.h>
# include <stdio.h>
# include "tokenizer.h"

typedef struct			s_child_list
{
	struct s_child_list	*next;
	struct s_ast		*child;
}						t_child_list; 

void	free_child_list(t_child_list *t);
t_ast	*get_last_child(t_child_list *child_list);

typedef struct			s_ast
{
	struct s_ast		*parent;
	t_child_list		*child_list;
	char				*data;
	int					type;
	int					priority;
	int					(* execute)(struct s_ast *self);
}						t_ast;

t_ast	*build_ast(t_token *token);
void	destroy_ast(t_ast *ast);
void	print_ast(t_ast *a, int pref_len);

#endif 
