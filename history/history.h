#ifndef TERMINAL_HISTORY_H
# define TERMINAL_HISTORY_H

#include <stdlib.h>
#include <string.h> //Remove me later

typedef struct	s_history
{
	struct s_history	*older;
	struct s_history	*newer;
	char				*line;
}				t_history;


//public:
char			*set_cursor_value(char *line);
char			*get_cursor_value(void);

/*
 *				0 returned if cursor can't move (on history border)
 *				1 if cursore was moved
 */
int				move_cursor_to_older(void);
int				move_cursor_to_newer(void);

void			append_to_history(char *line);

//private:
t_history		*cursor(void);
t_history		*history(void);
t_history		*get_cursor(void);
t_history		*set_cursor(t_history *cursor);

#endif
