#include "nfa.h"

t_state	*create_double_quote_automaton(void)
{
	t_state		*s2;

	s2 = new_state(NON_FINAL, new_transition(double_quote_condition,
				new_state(FINAL, NULL)));
	append_transition(&s2->transition_list, not_double_quote_condition, s2);
	return (new_state(NON_FINAL, new_transition(double_quote_condition, s2)));
}

t_state	*double_quote_automaton(void)
{
	static t_state	*automaton;

	if (automaton == NULL)
		automaton = create_double_quote_automaton();
	return (automaton);
}
