#include <stdio.h>

static int			is_operator(char *s)
{
	if ((s[0] == '*' && s[1] == '*') && !is_operator(s + 2))
		return (1);
	return ((s[0] == '+' ||	\
			s[0] == '-' ||	\
			s[0] == '*' ||	\
			s[0] == '/') &&
			!is_operator(s + 1));
}

int			main(void)
{
	printf("%d\n", is_operator("-"));
}
