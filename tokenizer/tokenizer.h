#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../parser/automata/nfa.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h> // TODO: you know it

# define ARG_P		0
# define REDIR_P	1
# define PIPE_P		2

typedef struct s_token
{
	char			*data;
	int				priority;
	struct s_token	*next;
}				t_token;

void		resect_quotes_from_line(char **line);
t_token		*append_token_list(t_token **t, char *s, int priority);
void		free_token_list(t_token *t);
int			handle_envs(char **line);
void		replace_substring(char **line, int index,
				int len, char *replacement);
char		*resect_substring(char **line, int start, int length);
char		*insert_substring(char **line, int index, char *subs);

//			Print
void		print_token_list(t_token *t);

typedef struct s_tokenizer
{
	t_token	*token_list;
	int		(*exec)(struct s_tokenizer *, char **);
}				t_tokenizer;

void		resect_quotes(t_tokenizer	*self);
t_tokenizer	*new_tokenizer(void);
void		destroy_tokenizer(t_tokenizer *self);

#endif
