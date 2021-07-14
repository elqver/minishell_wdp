#include <stdlib.h>

static int	print_flags_singleton(int *new_val)
{
	static int	saved_val;

	if (new_val != NULL)
		saved_val = *new_val;
	return (saved_val);
}

int	get_printing_flags(void)
{
	return (print_flags_singleton(NULL));
}

int	set_printing_flags(int new_val)
{
	return (print_flags_singleton(&new_val));
}
