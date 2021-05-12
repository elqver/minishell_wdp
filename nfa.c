#include "nfa.h"

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
		if(transition->condition(c))
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
int	check_string(t_state *regex, char *s)
{
	int	f_was_correct;
	int	i;
	int	status;
	
	f_was_correct = 1;
	i = 0;
	while (s[i] != '\0')
	{
		status = change_state(&regex, s[i]);
		if (status == -1 && f_was_correct)
			return (i - 1);
		if (status == -1)
			return (-1);
		if (status == 1)
			f_was_correct = 1;
		i++;
	}
	if (status == 1)
		return (i - 1);
	return (-1);
}
