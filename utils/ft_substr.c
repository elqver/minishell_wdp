#include <stdlib.h>
#include "utils.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr = ft_calloc(1, sizeof(char));
		substr[0] = '\0';
		return (substr);
	}
	substr = ft_calloc((len + 1), sizeof(char));
	if (substr == NULL)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
