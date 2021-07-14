#include "nfa.h"

static t_state	*create_word_automaton(void)
{
	t_state	*sm;
	t_state	*ssq;
	t_state	*sdq;

	sm = new_state(FINAL, NULL);
	ssq = new_state(NON_FINAL, NULL);
	sdq = new_state(NON_FINAL, NULL);
	sm->transition_list = new_transition(word_symbol_condition, sm);
	append_transition(&sm->transition_list, double_quote_condition, sdq);
	append_transition(&sm->transition_list, single_quote_condition, ssq);
	ssq->transition_list = new_transition(not_single_quote_condition, ssq);
	append_transition(&ssq->transition_list, single_quote_condition, sm);
	sdq->transition_list = new_transition(not_double_quote_condition, sdq);
	append_transition(&sdq->transition_list, double_quote_condition, sm);
	return (sm);
}

t_state	*word_automaton(void)
{
	static t_state	*automaton;

	if (automaton == NULL)
		automaton = create_word_automaton();
	return (automaton);
}
