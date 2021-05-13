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
int	check_string(t_state *regex, char *s)
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
			return (match_found * i - 1);
		if (status == 1)
			match_found = 1;
		i++;
	}
	if (status == 1)
		return (i - 1);
	return (-1);
}

int			main(int ac, char **av)
{
	if (ac == 1)
	{
		printf("No input arguments\n");
		return (1);
	}
	char	*s = av[1];
	char	t;
	int		res;
	printf("Parsing %s\n", s);
	while (*s)
	{
		res = check_string(word_automaton(), s);
		if (res != -1)
		{
			t = *(s + res + 1);
			*(s + res + 1) = '\0';
			printf("				Word token: %s\n", s);
			*(s + res + 1) = t;
			s += res;
		}
		res = check_string(redir_automaton(), s);
		if (res != -1)
		{
			t = *(s + res + 1);
			*(s + res + 1) = '\0';
			printf("				Redir token: %s\n", s);
			*(s + res + 1) = t;
			s += res;
		}
		res = check_string(pipe_automaton(), s);
		if (res != -1)
		{
			t = *(s + res + 1);
			*(s + res + 1) = '\0';
			printf("				Pipe token: %s\n", s);
			*(s + res + 1) = t;
			s += res;
		}
		s++;
	}
	return (0);
}
