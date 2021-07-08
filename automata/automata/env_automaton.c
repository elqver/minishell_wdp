#include "../nfa/nfa.h"

t_state	*env_automaton(void)
{
	t_state		*s1;
	t_state		*s2;

	s2 = new_state(1, 0, NULL);
	append_transition(&s2->transition_list, letter_digit_underscore_condition, s2);
	s1 = new_state(0, 1, new_transition(letter_underscore_condition, s2));
	return (s1);
}

