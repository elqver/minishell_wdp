#include <stdlib.h>
#include "utils.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dp;
	const unsigned char	*sp;

	dp = dst;
	sp = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n--)
		*dp++ = *sp++;
	return (dst);
}
