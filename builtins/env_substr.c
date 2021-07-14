#include "env_substr.h"
#include "../utils/utils.h"

static char	*_substr(char *str, char *start, char *end)
{
	char	*sub;

	if (str == NULL || start == NULL)
		return (NULL);
	if (end == NULL)
		end = ft_strchr(str, '\0');
	sub = ft_calloc(sizeof(char), end - start + 1);
	if (sub == NULL)
		return (NULL);
	sub = ft_strncpy(sub, start, end - start);
	return (sub);
}

char	*var_substr(char *str)
{
	return (_substr(str, str, ft_strchr(str, '=')));
}

char	*val_substr(char *str)
{
	char	*eq_ptr;

	eq_ptr = ft_strchr(str, '=');
	if (eq_ptr == NULL)
		return (NULL);
	return (_substr(str, eq_ptr + 1, ft_strchr(str, '\0')));
}
