#include "nfa.h"

static t_state	*create_dollar_env_automaton(void)
{
	t_state	*s1;
	t_state	*s2;
	t_state	*s3;

	s3 = new_state(FINAL, NULL);
	append_transition(&s3->transition_list,
		letter_digit_underscore_condition, s3);
	s2 = new_state(NON_FINAL, new_transition(
				letter_underscore_condition, s3));
	s1 = new_state(NON_FINAL, new_transition(dollar_condition, s2));
	return (s1);
}

t_state	*dollar_env_automaton(void)
{
	static t_state	*automaton;

	if (automaton == NULL)
		automaton = create_dollar_env_automaton();
	return (automaton);
}

