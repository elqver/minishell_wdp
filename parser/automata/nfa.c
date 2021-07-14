#include "nfa.h"
#include "../../utils/utils.h"

t_state	*new_state(int final,
					t_transition *transition_list)
{
	t_state	*state;

	state = malloc(sizeof(t_state));
	state->final = final;
	state->transition_list = transition_list;
	return (state);
}

int	change_state(t_state **current_state, char c)
{
	t_transition	*transition;

	if (*current_state == NULL)
		return (-1);
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
