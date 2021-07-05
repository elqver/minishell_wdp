#include "../nfa/nfa.h"

static int	word_symbol_condition(char c)
{
	return (!strchr("><| \t\n\v\f\r", c));
}

static int		not_single_quote_condition(char c)
{
	return (c != '\'');
}

static int		single_quote_condition(char c)
{
	return (c == '\'');
}

static int	double_quote_condition(char c)
{
	return (c == '"');
}

static int	not_double_quote_condition(char c)
{
	return (c != '"');
}

t_state		*word_automaton(void)
{
	t_state			*sm; // state_main
	t_state			*ssq; // state_single_quote
	t_state			*sdq; // state_double_quote

	sm = new_state(1, 1, NULL);
	ssq = new_state(0, 0, NULL);
	sdq = new_state(0, 0, NULL);

	sm->transition_list = new_transition(word_symbol_condition, sm);
	append_transition(&sm->transition_list, double_quote_condition, sdq);
	append_transition(&sm->transition_list, single_quote_condition, ssq);

	ssq->transition_list = new_transition(not_single_quote_condition, ssq);
	append_transition(&ssq->transition_list, single_quote_condition, sm);

	sdq->transition_list = new_transition(not_double_quote_condition, sdq);
	append_transition(&ssq->transition_list, double_quote_condition, sm);

	return (sm);
}
