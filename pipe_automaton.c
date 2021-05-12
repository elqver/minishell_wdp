#include "condition.h"
#include "nfa.h"
#include "transition.h"

int		pipe_condition(char c)
{
	return (c == '|');
}

t_state	*pipe_automaton(void)
{
	return (new_state(0, 1, new_transition(pipe_condition, new_state(1, 0, NULL))));
}

int main(int ac, char **argv)
{
	printf("argv[1] = %s\n", argv[1]);
	printf("check automaton: %d\n", check_string(pipe_automaton(), argv[1]));
}
