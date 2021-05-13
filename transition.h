#ifndef TRANSITION_H
# define TRANSITION_H

# include <stdlib.h>
# include <stdio.h>

typedef struct			s_transition
{
	int					(* condition)(char c);
	struct s_state		*target;
	struct s_transition	*next;
}						t_transition;

t_transition		*new_transition(int (* condition)(char c),
										struct s_state *target);

t_transition		*append_transition(t_transition **transition_list,
											int (*condition)(char c),
											struct s_state *target);

#endif
