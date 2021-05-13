#include "nfa.h"
#include "automata.h"

t_state					*new_state(int final,
										int initial,
										t_transition *transition_list)
{
	t_state	*state;

	state = malloc(sizeof(t_state));
	state->final = final;
	state->initial = initial;
	state->transition_list = transition_list;

	return (state);
}

int						change_state(t_state **current_state, char c)
{
	t_transition	*transition;

	if (*current_state == NULL)
	{
		printf("strange thing happend -> current_state of automate is NULL\n");
		return (-1);
	}
	transition = (*current_state)->transition_list;
	while (transition != NULL)
	{
		if (transition->condition(c))
		{
			*current_state = transition->target;
			return (transition->target->final);
		}
		transition = transition->next;
	}
	return (-1);
}

/*
 * returns -1 if s doesn't match regex
 * returns length of pattern otherwise
 */
int	get_lexeme_len(t_state *regex, char *s)
{
	int	i;
	int	status;
	int	match_found;
	
	i = 0;
	match_found = 0;
	while (s[i])
	{
		status = change_state(&regex, s[i]);
		if (status == -1)
			return (match_found * (i + 1) - 1);
		if (status == 1)
			match_found = 1;
		i++;
	}
	if (status == 1)
		return (i);
	return (-1);
}

t_state_list			*new_state_list(t_state *state)
{
	t_state_list *state_list_node;

	state_list_node = calloc(sizeof(t_state_list), 1);
	state_list_node->state = state;
	return (state_list_node);
}

void					append_state_list(t_state_list **state_list,
											t_state *state)
{
	t_state_list	*tmp;

	if (*state_list == NULL)
	{
		*state_list = new_state_list(state);
		return ;
	}
	tmp = *state_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_state_list(state);
}

void					free_state_list(t_state_list *state_list)
{
	t_state_list	*tmp;

	while (state_list != NULL)
	{
		tmp = state_list->next;
		free_transiton_list(state_list->state->transition_list);
		free(state_list->state);
		state_list = tmp;
	}
}

static int 				is_state_in_state_list(t_state_list *state_list,
												t_state *state)
{
	while (state_list != NULL)
	{
		if (state_list->state == state)
			return (1);
		state_list = state_list->next;
	}
	return (0);
}

static void				expand_state_list_from_state(t_state_list *state_list,
														t_state *state)
{
	t_transition	*transition;

	if (state == NULL || is_state_in_state_list(state_list, state))
		return ;
	append_state_list(&state_list, state);
	transition = state->transition_list;
	while (transition != NULL)
	{
		expand_state_list_from_state(state_list, transition->target);
		transition = transition->next;
	}
}

static t_state_list 	*find_all_automaton_nodes(t_state *state)
{
	t_state_list *state_list;

	state_list = NULL;
	expand_state_list_from_state(state_list, state);
	return (state_list);
}

void					destroy_regex(t_state *state)
{
	free_state_list(find_all_automaton_nodes(state));
}
