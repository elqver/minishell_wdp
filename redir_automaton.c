#include "condition.h"
#include "nfa.h"
#include "transition.h"

int		right_redir_condition(char c)
{
	return (c == '>');
}

int		left_redir_condition(char c)
{
	return (c == '<');
}

t_state	*redir_automaton(void)
{
	t_state			*s1;
	t_state			*s2;
	t_state			*s3;
	t_transition	*t1;
	t_transition	*t2;
	t_transition	*t3;
	t_transition	*t4;


}

/*
t_state	*automaton(void)
{
	return (new_state(0, 1,
			new_transition(right_redir_condition,
			new_state(1, 0,
			new_transition(right_redir_condition,
			new_state(1, 0, NULL))))));
}
*/

int main(int ac, char **argv)
{
	printf("argv[1] = %s\n", argv[1]);
	printf("check automaton: %d\n", check_string(redir_automaton(), argv[1]));
}
