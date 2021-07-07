#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../automata/nfa/nfa.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h> // TODO: you know it

# define ARG_P		0
# define REDIR_P	1
# define PIPE_P		2

typedef struct		s_token
{
	char			*data;
	int				priority;
	struct s_token	*next;
}					t_token;

void			print_token_list(t_token *t);
t_token			*new_token(char *s, int priority);
t_token			*append_token_list(t_token **t, char *s, int priority);
void			free_token_list(t_token *t);
t_token			*get_last_token(t_token *t);

int				handle_envs(char **line);
int				resect_quotes(char **line);

typedef struct		s_tokenizer
{
	t_token			*token_list;
	int				(* exec)(struct s_tokenizer *, char **);
}					t_tokenizer;

t_tokenizer		*new_tokenizer(void);
void			destroy_tokenizer(t_tokenizer *self);

#endif
