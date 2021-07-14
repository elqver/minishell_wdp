#include "conditions.h"
#include "../../utils/utils.h"

int	letter_underscore_condition(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	letter_digit_underscore_condition(char c)
{
	return (ft_isalnum(c) || c == '_');
}
