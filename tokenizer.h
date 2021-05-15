#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "automata.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h> // TODO: you know it

# define WORD		1
# define SQUOT		2
# define DQUOT		3
# define REDIR		4
# define PIPE		5
# define COMMAND	6

# define ARG_P		0
# define COMMAND_P	1
# define PIPE_P		2

typedef struct		s_token
{
	char			*data;
	int				type;
	int				priority;
	struct s_token	*next;
}					t_token;

void			print_token_list(t_token *t);
t_token			*new_token(char *s, int type, int priority);
t_token			*append_token_list(t_token **t, char *s, int type, int priority);
void			free_token_list(t_token *t);
t_token			*get_last_token(t_token *t);

typedef struct		s_tokenizer
{
	t_token			*token_list;
	int				(* exec)(struct s_tokenizer *, char *);
}					t_tokenizer;

t_tokenizer		*new_tokenizer(void);

/*
 * Usage scenario:
 *
 * tokenizer = new_tokenizer();
 * my_tokens_1 = tokenizer->exec(tokenizer, my_s_1);
 * my_tokens_2 = tokenizer->exec(tokenizer, my_s_2);
 */

#endif
