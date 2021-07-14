#include "nfa.h"

static t_state	*create_heredoc_automaton(void)
{
	t_state	*s2;
	t_state	*s3;
	t_state	*sm;
	t_state	*ssq;
	t_state	*sdq;

	ssq = new_state(NON_FINAL, NULL);
	sdq = new_state(NON_FINAL, NULL);
	sm = new_state(FINAL, NULL);
	sm->transition_list = new_transition(word_symbol_condition, sm);
	append_transition(&sm->transition_list, double_quote_condition, sdq);
	append_transition(&sm->transition_list, single_quote_condition, ssq);
	ssq->transition_list = new_transition(not_single_quote_condition, ssq);
	append_transition(&ssq->transition_list, single_quote_condition, sm);
	sdq->transition_list = new_transition(not_double_quote_condition, sdq);
	append_transition(&sdq->transition_list, double_quote_condition, sm);
	s3 = new_state(NON_FINAL, new_transition(word_symbol_condition, sm));
	append_transition(&s3->transition_list, space_condition, s3);
	append_transition(&s3->transition_list, single_quote_condition, ssq);
	append_transition(&s3->transition_list, double_quote_condition, sdq);
	s2 = new_state(NON_FINAL, new_transition(left_redir_condition, s3));
	return (new_state(NON_FINAL, new_transition(left_redir_condition, s2)));
}

t_state	*heredoc_automaton(void)
{
	static t_state	*automaton;

	if (automaton == NULL)
		automaton = create_heredoc_automaton();
	return (automaton);
}
