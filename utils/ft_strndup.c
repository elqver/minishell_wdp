#include <stdlib.h>

char	*ft_strndup(const char *s, size_t n)
{
	char			*res;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	res = malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
