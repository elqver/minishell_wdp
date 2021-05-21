#include "input.h"

t_backup	*new_backup(t_string *s, void *addr)
{
	t_backup	*new;

	new = calloc(sizeof(t_backup), 1);
	new->data = copy_string(s);
	new->addr = addr;
	return (new);
}

static int	is_addr_in_backup_list(t_backup *b, void *addr)
{
	while (b != NULL)
	{
		if (b->addr == addr)
			return (1);
		b = b->next;
	}
	return (0);
}

/*
t_backup	*push_backup(t_backup **b, t_string *s, void *addr)
{
	t_backup	*new;

	if (*b == NULL)
	{
		*b = new_backup(s, addr);
		return (*b);
	}
	if (is_addr_in_backup_list(*b, addr) == 1)
		return (*b);
	new = new_backup(s, addr);
	new->next = *b;
	*b = new;
	return (new);
}
*/

t_backup	*push_backup(t_backup **b, t_history *history)
{
	t_backup	*new;

	if (*b == NULL)
	{
		*b = new_backup(history->data, history);
		return (*b);
	}
	if (is_addr_in_backup_list(*b, history) == 1)
		return (*b);
	new = new_backup(history->data, history);
	new->next = *b;
	*b = new;
	return (new);

}

void		destroy_backup(t_backup *b)
{
	del_string(b->data);
	free(b);
}

void	clear_backup_list(t_backup *b)
{
	t_backup	*tmp;

	while (b != NULL)
	{
		tmp = b->next;
		destroy_backup(b);
		b = tmp;
	}
}
