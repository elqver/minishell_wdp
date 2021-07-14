#include <stdlib.h>
#include "utils.h"

char	*ft_strchr(const char *s, int c)
{
	char	*res;

	res = (char *)s;
	if ((char)c == '\0')
		return (res + ft_strlen(res));
	while (*res != (char)c && *res != '\0')
		res++;
	if (*res == '\0')
		return (NULL);
	return (res);
}
