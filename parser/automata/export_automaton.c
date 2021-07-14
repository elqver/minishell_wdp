#include "nfa.h"

static t_state	*create_export_automaton(void)
{
	t_state		*s1;
	t_state		*s2;

	s2 = new_state(FINAL, NULL);
	append_transition(&s2->transition_list,
		letter_digit_underscore_condition, s2);
	s1 = new_state(NON_FINAL, new_transition(letter_underscore_condition, s2));
	return (s1);
}

t_state	*export_automaton(void)
{
	static t_state	*automaton;

	if (automaton == NULL)
		automaton = create_export_automaton();
	return (automaton);
}
