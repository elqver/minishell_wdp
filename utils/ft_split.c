#include <stdlib.h>
#include "utils.h"

static int	count_words(char const *s, char delimeter)
{
	char	in_word;
	size_t	result;

	in_word = 0;
	result = 0;
	while (*s != '\0')
	{
		if (in_word && *s == delimeter)
			in_word = 0;
		else if (!in_word && *s != delimeter)
		{
			in_word = 1;
			result += 1;
		}
		s++;
	}
	return (result);
}

static void	skip_delimeter(char const **s, char delimeter)
{
	while (**s == delimeter && **s != '\0')
		(*s)++;
}

static char	*pick_out_word(char const **s, char delimeter)
{
	char	*word;
	char	*sc;

	skip_delimeter(s, delimeter);
	sc = ft_strchr(*s, delimeter);
	if (sc == NULL)
		word = (char *)malloc((ft_strlen(*s) + 1) * sizeof(char));
	else
		word = (char *)malloc(((sc - *s) + 1) * sizeof(char));
	ft_strlcpy(word, *s, (int)(sc - *s + 1));
	*s = sc;
	return (word);
}

void	clean(char **res, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(res[i]);
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		word_number;
	int		cw;

	if (s == NULL)
		return (NULL);
	cw = count_words(s, c);
	res = (char **)malloc((cw + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	word_number = 0;
	while (word_number < cw)
	{
		res[word_number] = pick_out_word(&s, c);
		if (res[word_number] == NULL)
		{
			clean(res, word_number - 1);
			free(res);
			return (NULL);
		}
		word_number++;
	}
	res[word_number] = NULL;
	return (res);
}
