#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "utils.h"

static char		**n_words(char const *s, char c)
{
	int    		 i;
	int    		 b;
	int    		 count;
    i = 0;
    count = 0;
    b = ft_strlen(s);
    while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || i + 1 == b))
			count++;
		i++;
	}
	return (char **)malloc((count + 1) * sizeof(char *));
}

char			**ft_split(char const *s, char c)
{
	int			i;
	int			n_s;
	int			b;
	int			start;
	char		**sp_s;

	if (s == NULL && c != '\0')
		return (NULL);

	i = 0;
	n_s = 0;
	start = 0;
	b = ft_strlen(s);
	printf("%d << b\n", b);
	sp_s = n_words(s, c);
	while (s[i] && i < b)
	{
		printf("%d\n", i);
		if (s[i] != c)
		{
			start = i;
			while (s[i] !=c && i < b)
				i++;
			sp_s[n_s++] = ft_substr(s, start, i - start);
		}
		i++;
	}
	sp_s[n_s] = NULL;
	return (sp_s);
}
