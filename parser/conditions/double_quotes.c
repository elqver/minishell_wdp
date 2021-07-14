#include "conditions.h"

int	double_quote_condition(char c)
{
	return (c == '"');
}

int	not_double_quote_condition(char c)
{
	return (c != '"');
}
