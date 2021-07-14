#include "conditions.h"
#include "../../utils/utils.h"

int	word_symbol_condition(char c)
{
	return (!ft_strchr("><| \t\n\v\f\r\'\"", c));
}
