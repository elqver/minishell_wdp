#include "conditions.h"

int	right_redir_condition(char c)
{
	return (c == '>');
}

int	left_redir_condition(char c)
{
	return (c == '<');
}
