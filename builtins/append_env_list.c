#include "env.h"
#include "../automata/nfa/nfa.h"

#include <ctype.h> // TODO: delete

static int	letter_underscore_condition(char c)
{
	return (isalpha(c) || c == '_');
}

static int	letter_digit_underscore_condition(char c)
{
	return (isalnum(c) || c == '_');
}

static t_state	*create_export_automaton(void)
{
	t_state		*s1;
	t_state		*s2;

	s2 = new_state(1, 0, NULL);
	append_transition(&s2->transition_list, letter_digit_underscore_condition, s2);
	s1 = new_state(0, 1, new_transition(letter_underscore_condition, s2));
	return (s1);
}

static t_env	*_append_env_list(t_env **list, char *var, char *val)
{
	if (*list == NULL)
		return (*list = new_env_node(var, val));
	return (_append_env_list(&((*list)->next), var, val));
}

t_env	*append_env_list(char *var, char *val)
{
	static t_state	*export_automaton;
	t_env			*tmp;

	if (export_automaton == NULL)
		export_automaton = create_export_automaton();
	if (get_lexeme_len(export_automaton, var) == -1)
		return (NULL);
	tmp = find_env_var(var);
	if (tmp)
	{
		free(tmp->val);
		tmp->val = strdup(val); // TODO: replace with ft_
		return (tmp);
	}
	return (_append_env_list(env_list(get), var, val));
}
