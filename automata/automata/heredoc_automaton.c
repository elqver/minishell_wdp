#include "../nfa/nfa.h"

static int	left_redir_condition(char c)
{
	return (c == '<');
}

static int	word_symbol_condition(char c)
{
	return (!strchr("><| \t\n\v\f\r\'\"", c));
}

t_state	*heredoc_automaton(void)
{
	t_state	*s1;
	t_state	*s2;
	t_state	*s3;
	t_state	*s4;

	s4 = new_state(1, 0, NULL);
	s4->transition_list = new_transition(word_symbol_condition, s4);
	s3 = new_state(0, 0, new_transition(word_symbol_condition, s4));

	return (s1);
}
