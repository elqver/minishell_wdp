#include <stdlib.h>
#include "utils.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	ls1;
	size_t	ls2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	join = (char *)ft_calloc(ls1 + ls2 + 1, sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_strlcpy(join, s1, ls1 + 1);
	ft_strlcpy(join + ls1, s2, ls2 + 1);
	return (join);
}
