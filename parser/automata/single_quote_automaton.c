#include "../nfa/nfa.h"

t_state	*single_quote_automaton(void)
{
	t_state	*s2;

	s2 = new_state(0, 0, new_transition(
				single_quote_condition, new_state(1, 0, NULL)));
	append_transition(&s2->transition_list, not_single_quote_condition, s2);
	return (new_state(0, 1, new_transition(single_quote_condition, s2)));
}
