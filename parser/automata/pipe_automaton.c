#include "nfa.h"

static t_state	*create_pipe_automaton(void)
{
	return (new_state(NON_FINAL,
			new_transition(pipe_condition, new_state(FINAL, NULL))));
}

t_state	*pipe_automaton(void)
{
	static t_state	*automaton;

	if (automaton == NULL)
		automaton = create_pipe_automaton();
	return (automaton);
}
