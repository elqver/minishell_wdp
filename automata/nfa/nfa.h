#ifndef NFA_H
# define NFA_H

# include <stdio.h>
# include <stdlib.h>
# include "../transition/transition.h"
# include <string.h>					// TODO: replace
# include <ctype.h>						// TODO: replace

typedef struct			s_state 
{
	int					final;
	int					initial;
	t_transition		*transition_list;
}						t_state;

t_state					*new_state(int final,
										int initial,
										t_transition *transition_list);
int						change_state(t_state **current_state, char c);
int						get_lexeme_len(t_state *regex, char *s);
void					destroy_regex(t_state *state);

typedef struct			s_state_list
{
	t_state				*state;
	struct s_state_list	*next;
}						t_state_list;

t_state_list			*new_state_list(t_state *state);
void					append_state_list(t_state_list **state_list,
											t_state *state);
void					free_state_list(t_state_list *state_list);

t_state	*word_automaton(void);
t_state	*single_quote_automaton(void);
t_state	*double_quote_automaton(void);
t_state	*redir_automaton(void);
t_state	*pipe_automaton(void);

#endif
