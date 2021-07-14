#include "../nfa/nfa.h"

t_state	*redir_automaton(void)
{
	t_state	*initial;
	t_state	*one_lr;
	t_state	*one_rr;

	one_lr = new_state(1, 0, new_transition(left_redir_condition,
				new_state(1, 0, NULL)));
	one_rr = new_state(1, 0, new_transition(right_redir_condition,
				new_state(1, 0, NULL)));
	initial = new_state(0, 1, NULL);
	append_transition(&(initial->transition_list),
		left_redir_condition, one_lr);
	append_transition(&(initial->transition_list),
		right_redir_condition, one_rr);
	return (initial);
}
