#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>

typedef struct		s_token
{
	char			*data;
	struct s_token	*next;
}					t_token;

typedef struct		s_tokenizer
{
	t_token			*lst;
	int				(*state)(struct s_tokenizer *, char);
}					t_tokenizer;

t_token		*tokenizer(char *s);
void		print_token_list(t_token *t);
int			num_state(t_tokenizer *t, char c);
int			space_state(t_tokenizer *t, char c);
int			op_state(t_tokenizer *t, char c);

#endif
