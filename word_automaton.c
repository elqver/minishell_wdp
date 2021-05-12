#include "condition.h"
#include "nfa.h"
#include "transition.h"

#include <string.h> // TODO: replace

int			word_symbol_condition(char c)
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

int			main(int ac, char **av)
{
	printf("Parsing %s\n", av[1]);
	printf("Result: %d\n", check_string(word_automaton(), av[1]));
}
