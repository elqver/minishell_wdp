#include "../nfa/nfa.h"

static int	word_symbol_condition(char c)
{
	return (!strchr("><| \t\n&\"\'#()", c));
}

t_state		*word_automaton(void)
{
	t_state			*s;
	t_transition	*t;

	s = new_state(1, 1, NULL);
	t = new_transition(word_symbol_condition, s);
	s->transition_list = t;
	return (s);
}
