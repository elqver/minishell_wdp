#include "history.h"


t_history		*history_singleton(t_history *history_pointer)
{
	static t_history	*history;

	if (history_pointer)
		history = history_pointer;
	if (!history)
		history = calloc(sizeof(t_history), 1); //replace calloc later
	return (history);
}

t_history		*get_history(void)
{
	return (history_singleton(NULL));
}

t_history		*set_history(t_history *history)
{
	return (history_singleton(history));
}

t_history		*cursor_singleton(t_history *cursor_pointer)
{
	static t_history	*cursor;

	if (cursor_pointer)
		cursor = cursor_pointer;
	if (!cursor)
		cursor = get_history();
	return (cursor);
}

t_history		*get_cursor(void)
{
	return (cursor_singleton(NULL));
}

t_history		*set_cursor(t_history *cursor)
{
	return (cursor_singleton(cursor));
}

char			*get_cursor_value(void)
{
	t_history	*cursor_pointer;

	cursor_pointer = get_cursor();
	return (strdup(cursor_pointer->line)); //replace strdup
}

char			*set_cursor_value(char *line)
{
	t_history	*cursor_pointer;

	cursor_pointer = get_cursor();
	free(cursor_pointer->line);
	cursor_pointer->line = strdup(line); //replace strdup
	return (line);
}

int				move_cursor_to_older(void)
{
	t_history	*cursor_pointer;

	cursor_pointer = get_cursor();
	if (cursor_pointer->older)
	{
		set_cursor(cursor_pointer->older);
		return (1);
	}
	return (0);
}

int				move_cursor_to_newer(void)
{
	t_history	*cursor_pointer;

	cursor_pointer = get_cursor();
	if (cursor_pointer->newer)
	{
		set_cursor(cursor_pointer->newer);
		return (1);
	}
	return (0);
}

void			append_to_history(char *line)
{
	t_history	*node_to_append;

	if (get_history()->line == NULL)
	{
		get_history()->line = strdup(line);
		return ;
	}
	node_to_append = calloc(sizeof(t_history), 1); //replace calloc later
	get_history()->newer = node_to_append;
	node_to_append->line = strdup(line); //replace strdup later
	node_to_append->older = get_history();
	set_history(node_to_append);
	set_cursor(get_history());
}
