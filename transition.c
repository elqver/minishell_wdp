#include "transition.h"

t_transition		*new_transition(int (* condition)(char c),
										struct s_state *target)
{
	t_transition	*transition;

	transition = calloc(1, sizeof(t_transition));
	transition->target = target;
	transition->condition = condition;

	return (transition);
}

t_transition		*append_transition(t_transition **transition_list,
											int (*condition)(char c),
											struct s_state *target)
{
	t_transition	*ptr;

	if (*transition_list == NULL)
	{
		*transition_list = new_transition(condition, target); 
		return (*transition_list);
	}
	ptr = *transition_list;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new_transition(condition, target);

	return (*transition_list);
}
