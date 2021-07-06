#include "env.h"

// TODO:
// this function is written twice.
// reorganize stuff ?
static t_env	*_append_env_list(t_env **list, char *var, char *val)
{
	if (*list == NULL)
		return (*list = new_env_node(var, val));
	return (_append_env_list(&((*list)->next), var, val));
}

// TODO:
// this function is written twice.
// reorganize stuff ?
static void	print_sorted_list(t_env *list)
{
	while (list != NULL)
	{
		write(1, "declare -x ", 11);
		print_env(list->var, list->val);
		list = list->next;
	}
}

static void	_delete_env_list(t_env **list)
{
	t_env	*t;

	while (*list != NULL)
	{
		t = (*list)->next;
		free((*list)->var);
		free((*list)->val);
		free(*list);
		*list = t;
	}
}

static t_env	*_copy_list(t_env *list)
{
	t_env	*new;

	new = NULL;
	while (list != NULL)
	{
		_append_env_list(&new, list->var, list->val);
		// if (...error...)
		// 	...free stuff...
		// 	return (NULL);
		list = list->next;
	}
	return (new);
}

static t_env	*copy_list(void)
{
	return (_copy_list(*env_list(get)));
}

static void	swap(char **a, char **b)
{
	char	*t;

	t = *a;
	*a = *b;
	*b = t;
}

// tcs == two cycle sort
static void	*tcs(t_env *p1, t_env *p2, int i)
{
	if (p1 == NULL || p2 == NULL)
		return (NULL);
	if ((p1->var[i] == p2->var[i]) && p1->var[i])
		return (tcs(p1, p2, i + 1));
	if (p1->var[i] > p2->var[i])
		swap(&(p1->var), &(p2->var));
	if (p2->next != NULL)
		return (tcs(p1, p2->next, 0));
	return (tcs(p1->next, p1->next->next, 0));
}

void	sort_alphabetically(t_env *list)
{
	tcs(list, list->next, 0);
}

t_ast	*declare_x(void)
{
	t_env	*copy;

	copy = copy_list();
	if (copy == NULL)
		return (NULL);
	sort_alphabetically(copy);
	print_sorted_list(copy);
	_delete_env_list(&copy);
	return ((void *) -1); // that means everything went well
}

int	main(int ac, char **av, char **envp)
{
	create_env_list(envp);
	declare_x();
	delete_env_list();
}
