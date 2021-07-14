#include "nfa.h"

static t_state	*create_single_quote_automaton(void)
{
	t_state	*s2;

	s2 = new_state(NON_FINAL, new_transition(
				single_quote_condition, new_state(FINAL, NULL)));
	append_transition(&s2->transition_list, not_single_quote_condition, s2);
	return (new_state(NON_FINAL, new_transition(single_quote_condition, s2)));
}

t_state	*single_quote_automaton(void)
{
	static t_state	*automaton;

	if (automaton == NULL)
		automaton = create_single_quote_automaton();
	return (automaton);
}
