#include "nfa.h"
#include "../../utils/utils.h"

static void	expand_state_list_from_state(t_state_list **state_list,
				t_state *state)
{
	t_transition	*transition;

	if (state == NULL || is_state_in_state_list(*state_list, state))
		return ;
	append_state_list(state_list, state);
	transition = state->transition_list;
	while (transition != NULL)
	{
		expand_state_list_from_state(state_list, transition->target);
		transition = transition->next;
	}
}

static t_state_list	*find_all_automaton_nodes(t_state *automaton)
{
	t_state_list	*state_list;

	state_list = NULL;
	expand_state_list_from_state(&state_list, automaton);
	return (state_list);
}

void	destroy_regex(t_state *automaton)
{
	free_state_list(find_all_automaton_nodes(automaton));
}

void	destroy_automata(void)
{
	destroy_regex(pipe_automaton());
	destroy_regex(word_automaton());
	destroy_regex(single_quote_automaton());
	destroy_regex(double_quote_automaton());
	destroy_regex(env_automaton());
	destroy_regex(dollar_env_automaton());
	destroy_regex(export_automaton());
	destroy_regex(redir_automaton());
	destroy_regex(heredoc_automaton());
}
