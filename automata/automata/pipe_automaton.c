#include "../nfa/nfa.h"

static int	pipe_condition(char c)
{
	return (c == '|');
}

t_state		*pipe_automaton(void)
{
	return (new_state(0, 1, new_transition(pipe_condition, new_state(1, 0, NULL))));
}
