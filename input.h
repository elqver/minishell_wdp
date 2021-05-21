#ifndef INPUT_H
# define INPUT_H

# include <stdlib.h>

# include <string.h>
# include <stdio.h>

# define UP			1
# define DOWN		2
# define LEFT		3
# define RIGHT		4
# define BACKSPACE	5

typedef struct		s_string
{
	char			*string;
	unsigned		size;
	unsigned		i;
}					t_string;

t_string	*new_string(void);
t_string	*copy_string(t_string *src);
void		append_string(t_string *self, char c);
char		pop_string(t_string *self);
void		del_string(t_string *self);

typedef struct			s_history
{
	t_string			*data;
	struct s_history	*older;
	struct s_history	*newer;
}						t_history;

t_history	*new_history_node(t_string *s);
t_history	*push_history(t_history **h, t_string *s);
t_history	*get_newest_entry(t_history *h);

typedef struct			s_backup
{
	t_string			*data;
	void				*addr;
	struct s_backup		*next;
}						t_backup;

t_backup	*new_backup(t_string *s, void *addr);
t_backup	*push_backup(t_backup **b, t_history *h);
void		destroy_backup(t_backup *b);
void		clear_backup_list(t_backup *b);

#endif
