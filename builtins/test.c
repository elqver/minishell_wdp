#include <stdio.h>

int	i(int (*action)(int *));
int	inc(int *i);
int	dec(int *i);
int	get(int *i);

int	i(int (*action)(int *))
{
	static int	i;

	return (action(&i));
}

int	get(int *i)
{
	return (*i);
}

int	inc(int *i)
{
	return (++(*i));
}

int	dec(int *i)
{
	return (--(*i));
}

void	print(int i)
{
	printf("%d\n", i);
}

int	main(void)
{
	print(i(get));
	print(i(dec));
	print(i(dec));
}
