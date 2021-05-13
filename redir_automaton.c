#include "automata.h"

static int	right_redir_condition(char c)
{
	return (c == '>');
}

static int	left_redir_condition(char c)
{
	return (c == '<');
}

static int	digit_condition(char c)
{
	return (isdigit(c)); // TODO: replace with own
}

t_state		*redir_automaton(void)
{
	t_state		*s1;
	t_state		*s2;
	t_state		*s3;
	t_state		*s4;

	s4 = new_state(1, 0, NULL);
	s3 = new_state(1, 0, new_transition(right_redir_condition, s4));
	s2 = new_state(0, 0, new_transition(right_redir_condition, s3));
	append_transition(&s2->transition_list, digit_condition, s2);
	s1 = new_state(0, 1, new_transition(left_redir_condition, s4));
	append_transition(&s1->transition_list, right_redir_condition, s3);
	append_transition(&s1->transition_list, digit_condition, s2);
	return (s1);
}
