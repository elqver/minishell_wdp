#include <stdlib.h>
#include "utils.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*pd;
	const char	*ps;

	pd = dst;
	ps = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (!len)
		return (dst);
	if (pd <= ps)
		return (ft_memcpy(dst, src, len));
	pd += len;
	ps += len;
	while (len--)
		*--pd = *--ps;
	return (dst);
}
