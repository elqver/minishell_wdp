#include "nfa.h"
#include "../../utils/utils.h"

static t_state_list	*new_state_list(t_state *state)
{
	t_state_list	*state_list_node;

	state_list_node = ft_calloc(sizeof(t_state_list), 1);
	state_list_node->state = state;
	return (state_list_node);
}

void	append_state_list(t_state_list **state_list,
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

void	free_state_list(t_state_list *state_list)
{
	t_state_list	*tmp;

	while (state_list != NULL)
	{
		tmp = state_list->next;
		free_transiton_list(state_list->state->transition_list);
		free(state_list->state);
		free(state_list);
		state_list = tmp;
	}
}

int	is_state_in_state_list(t_state_list *state_list,
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
