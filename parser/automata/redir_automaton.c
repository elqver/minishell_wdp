#include "nfa.h"

static t_state	*create_redir_automaton(void)
{
	t_state	*initial;
	t_state	*one_lr;
	t_state	*one_rr;

	one_lr = new_state(FINAL, new_transition(left_redir_condition,
				new_state(FINAL, NULL)));
	one_rr = new_state(FINAL, new_transition(right_redir_condition,
				new_state(FINAL, NULL)));
	initial = new_state(NON_FINAL, NULL);
	append_transition(&(initial->transition_list),
		left_redir_condition, one_lr);
	append_transition(&(initial->transition_list),
		right_redir_condition, one_rr);
	return (initial);
}

t_state	*redir_automaton(void)
{
	static t_state	*automaton;

	if (automaton == NULL)
		automaton = create_redir_automaton();
	return (automaton);
}
