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

t_token		*tokenizer(char *s);
void		print_token_list(t_token *t);

#endif
