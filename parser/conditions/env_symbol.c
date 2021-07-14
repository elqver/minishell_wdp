#include "conditions.h"

int	letter_underscore_condition(char c)
{
	return (isalpha(c) || c == '_');
}

int	letter_digit_underscore_condition(char c)
{
	return (isalnum(c) || c == '_');
}
