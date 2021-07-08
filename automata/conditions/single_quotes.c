#include "conditions.h"

int	not_single_quote_condition(char c)
{
	return (c != '\'');
}

int	single_quote_condition(char c)
{
	return (c == '\'');
}

