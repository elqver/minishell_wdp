#include "env.h"

static void	print_sorted_list(t_env *list)
{
	while (list != NULL)
	{
		write(1, "declare -x ", 11);
		print_env(list->var, list->val);
		list = list->next;
	}
}

static t_env	*copy_list(t_env *list)
{
	t_env	*new;

	new = NULL;
	while (list != NULL)
	{
		_append_env_list(&new, list->var, list->val);
		list = list->next;
	}
	return (new);
}

static void	swap(t_env *a, t_env *b)
{
	char	*t;

	t = a->var;
	a->var = b->var;
	b->var = t;
	t = a->val;
	a->val = b->val;
	b->val = t;
}

// tcs == two cycle sort
static void	*tcs(t_env *p1, t_env *p2, int i)
{
	if (p1 == NULL || p2 == NULL)
		return (NULL);
	if ((p1->var[i] == p2->var[i]) && p1->var[i])
		return (tcs(p1, p2, i + 1));
	if (p1->var[i] > p2->var[i])
		swap(p1, p2);
	if (p2->next != NULL)
		return (tcs(p1, p2->next, 0));
	return (tcs(p1->next, p1->next->next, 0));
}

void	sort_alphabetically(t_env *list)
{
	tcs(list, list->next, 0);
}

int	declare_x(void)
{
	t_env	*copy;

	copy = copy_list(*env_list(get));
	sort_alphabetically(copy);
	print_sorted_list(copy);
	_delete_env_list(&copy);
	return (0);
}
