#include <stdlib.h>
#include "utils.h"

char	*ft_strdup(const char *s1)
{
	char	*res;

	if (s1 == NULL)
		return (NULL);
	res = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, ft_strlen(s1) + 1);
	return (res);
}
