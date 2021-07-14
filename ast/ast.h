#ifndef AST_H
# define AST_H

# include <stdlib.h>
# include <stdio.h>
# include "../tokenizer/tokenizer.h"
# include "../signals/signal_modes.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_ast
{
	struct s_ast		*left;
	struct s_ast		*right;
	char				*data;
	int					priority;
	int					type;
	int					(*exec)(struct s_ast *self);
}				t_ast;

//		Singleton
t_ast	*get_ast(void);
t_ast	*set_ast(t_ast *new_ptr);

//		Main ast functions
t_ast	*build_ast(t_token *token);
t_ast	*create_ast_node(t_token *token);
t_ast	*insert_ast_node(t_ast **ast, t_ast *node);
void	*destroy_ast(t_ast *ast);
void	execute_ast(void);

//		Heredoc
void	handle_heredocs(void);
void	handle_heredoc_node(t_ast *self);

//		Printing functions
void	print_ast(t_ast *root);
void	choose_color(int prefix_len);
void	white_color(void);

#endif 
