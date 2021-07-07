#include "env_substr.h"

// TODO:
// there's a lot of libft functions here
// that need to be replaced with ft_ analogs

static char	*_substr(char *str, char *start, char *end)
{
	char	*sub;

	if (str == NULL || start == NULL)
		return (NULL);
	if (end == NULL)
		end = strchr(str, '\0');
	sub = calloc(sizeof(char), end - start + 1);
	if (sub == NULL)
		return (NULL);
	sub = strncpy(sub, start, end - start);
	return (sub);
}

char	*var_substr(char *str)
{
	return (_substr(str, str, strchr(str, '=')));
}

char	*val_substr(char *str)
{
	char	*eq_ptr;

	eq_ptr = strchr(str, '=');
	if (eq_ptr == NULL)
		return (NULL);
	return (_substr(str, eq_ptr + 1, strchr(str, '\0')));
}
