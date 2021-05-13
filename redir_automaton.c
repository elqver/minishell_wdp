#include "automata.h"

static int	right_redir_condition(char c)
{
	return (c == '>');
}

static int	left_redir_condition(char c)
{
	return (c == '<');
}

t_state		*redir_automaton(void)
{
	t_state			*s3;
	t_transition	*t1_t2;

	s3 = new_state(1, 0, NULL);
	t1_t2 = new_transition(left_redir_condition, s3);
	append_transition(&t1_t2, right_redir_condition,
						new_state(1, 0,
						new_transition(right_redir_condition, s3)));
	return (new_state(0, 1, t1_t2));
}
