#include <stdlib.h>

static int	len_number(int n)
{
	int	i;

	i = n <= 0 ? 1 : 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*res;
	char	sign;
	int		len;

	len = len_number(n);
	sign = n < 0 ? -1 : 1;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[len--] = '\0';
	while (len + !!(sign + 1))
	{
		res[len--] = sign * (n % 10) + '0';
		n /= 10;
	}
	if (sign < 0)
		res[0] = '-';
	return (res);
}
