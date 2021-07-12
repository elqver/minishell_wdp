#include "ft_string.h"

#include <string.h> ///////////////////////////////////////////////////////////////////////////////////////////////////// DELETE

static size_t	ft_str_c_len(const char *s, char c)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void	skip_delim(char **s, char c)
{
	while (**s == c && **s)
		(*s)++;
}

static void	skip_word(char **s, char c)
{
	while (**s != c && **s)
		(*s)++;
}

static size_t	count_tokens(char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		skip_delim(&s, c);
		count++;
		skip_word(&s, c);
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	size_t	count = count_tokens(s, c);
	size_t	i = 0;
	size_t	j = 0;

	if (s == NULL)
		return (NULL);
	res = malloc(sizeof(char *) * (count + 1));
	while (*s)
	{
		skip_delim(&s, c);
		res[i] = malloc(ft_str_c_len(s, c) + 1);
		j = 0;
		while (*s != c && *s)
			res[i][j++] = *s++;
		res[i][j] = '\0';
		i++;
		skip_delim(&s, c);
	}
	res[i] = NULL;
	return (res);
}

char	*ft_strjoin(char const *a, char const *b)
{
	char	*r;
	size_t	alen;
	size_t	blen;

	alen = strlen(a);
	blen = strlen(b);
	r = malloc(alen + blen + 1);
	strcat(r, a);
	strcat(r, b);
	return (r);
}
