#include "../nfa/nfa.h"

t_state	*pipe_automaton(void)
{
	return (new_state(0, 1,
			new_transition(pipe_condition, new_state(1, 0, NULL))));
}
