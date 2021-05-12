#include "condition.h"
#include "nfa.h"
#include "transition.h"


t_state	*try_automaton()
{
	t_state			*automaton;
	t_state 		*second_state;
	t_state 		*final_state;
	t_transition	*tmp_transition_list;

	final_state = new_state(1, 0, NULL);

	second_state = new_state(0, 0, NULL);
	tmp_transition_list = new_transition(double_quote_condition, final_state);
	append_transition(&tmp_transition_list, basic_condititon, second_state);
	second_state->transition_list = tmp_transition_list;

	automaton = new_state(0, 1, new_transition(double_quote_condition, 
												second_state));

	return (automaton);
}

int main(int ac, char **argv)
{
	printf("argv[1] = %s\n", argv[1]);
	printf("check automaton: %d\n", check_string(try_automaton(), argv[1]));
}
