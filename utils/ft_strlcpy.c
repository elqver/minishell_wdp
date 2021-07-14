#include <stdlib.h>
#include "utils.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t srclen;

	if (dst == NULL || src == NULL)
		return (0);
	srclen = ft_strlen(src);
	if (srclen + 1 < dstsize)
		ft_memmove(dst, src, srclen + 1);
	else if (dstsize != 0)
	{
		ft_memmove(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (srclen);
}
