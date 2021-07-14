#include "tokenizer.h"

char	*resect_substring(char **line, int start, int length)
{
	char	*new_line;
	int		i;
	int		len;

	len = strlen(*line);
	new_line = malloc(len - length + 1); // TODO: take it out
	if (!new_line || start >= len || start + length > len
		|| start < 0 || length <= 0)
		return (NULL);
	i = -1;
	while (++i < start)
		new_line[i] = (*line)[i];
	i--;
	while (++i < len - length)
		new_line[i] = (*line)[i + length];
	new_line[i] = '\0';
	free(*line);
	*line = new_line;
	return (new_line);
}

char	*insert_substring(char **line, int index, char *subs)
{
	char	*new_line;
	int		line_len;
	int		subs_len;
	int		i;

	line_len = strlen(*line);
	subs_len = strlen(subs);
	new_line = malloc(line_len + subs_len + 1);
	i = -1;
	while (++i < index)
		new_line[i] = (*line)[i];
	i--;
	while (++i < index + subs_len)
		new_line[i] = subs[i - index];
	i--;
	while (++i < line_len + subs_len)
		new_line[i] = (*line)[i - subs_len];
	new_line[i] = '\0';
	free(*line);
	*line = new_line;
	return (new_line);
}

void	replace_substring(char **line, int index,
		int len, char *replacement)
{
	resect_substring(line, index, len);
	if (replacement == NULL)
		return ;
	insert_substring(line, index, replacement);
}
