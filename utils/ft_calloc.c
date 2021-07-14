#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*result;
	size_t	i;

	result = (char *)malloc(count * size);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < size * count)
		result[i++] = 0;
	return (void *)result;
}
