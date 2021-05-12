#include "condition.h"

int	double_quote_condition(char c)
{
	return (c == '"');
}

int single_quote_condition(char c)
{
	return (c == '\'');
}

int	basic_condititon(char c)
{
	return (c != '\0');
}
