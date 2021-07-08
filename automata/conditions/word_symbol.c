#include "conditions.h"

int	word_symbol_condition(char c)
{
	return (!strchr("><| \t\n\v\f\r\'\"", c));
}
