#include "../nfa/nfa.h"

t_state	*heredoc_automaton(void)
{
	t_state	*s1;
	t_state	*s2;
	t_state	*s3;
	t_state	*sm;
	t_state *ssq;
	t_state *sdq;

	sm = new_state(1, 0, NULL);
	ssq = new_state(0, 0, NULL);
	sdq = new_state(0, 0, NULL);

	sm->transition_list = new_transition(word_symbol_condition, sm);
	append_transition(&sm->transition_list, double_quote_condition, sdq);
	append_transition(&sm->transition_list, single_quote_condition, ssq);

	ssq->transition_list = new_transition(not_single_quote_condition, ssq);
	append_transition(&ssq->transition_list, single_quote_condition, sm);

	sdq->transition_list = new_transition(not_double_quote_condition, sdq);
	append_transition(&sdq->transition_list, double_quote_condition, sm);

	s3 = new_state(0, 0, new_transition(word_symbol_condition, sm));
	append_transition(&s3->transition_list, space_condition, s3);
	append_transition(&s3->transition_list, single_quote_condition, ssq);
	append_transition(&s3->transition_list, double_quote_condition, sdq);

	s2 = new_state(0, 0, new_transition(left_redir_condition, s3));
	s1 = new_state(0, 0, new_transition(left_redir_condition, s2));

	return (s1);
}
