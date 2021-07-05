#include "env.h"

t_env	**env_list(t_env **(* action)(t_env **))
{
	static t_env	*env_list;

	return (action(&env_list));
}

t_env	**get(t_env **env)
{
	return (env);
}

static t_env	*new_node(char *var)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->var = var;
	new->next = NULL;
	return (new);
}

t_env	*_append_env_list(t_env **env_list, char *var)
{
	if (*env_list == NULL)
		return (*env_list = new_node(var));
	return (_append_env_list(&((*env_list)->next), var));
}

t_env	*append_env_list(char *var)
{
	return (_append_env_list(env_list(get), var));
}

static void	_create_env_list(t_env **env_list, char **envp)
{
	unsigned int	i;

	i = 0;
	while (envp[i] != NULL)
		append_env_list(envp[i++]);
}

void	create_env_list(char **envp)
{
	return (_create_env_list(env_list(get), envp));
}

static void	_print_env_list(t_env *env_list)
{
	while (env_list != NULL)
	{
		printf("%s\n", env_list->var);
		env_list = env_list->next;
	}
}

void	print_env_list(void)
{
	_print_env_list(*env_list(get));
}

/*
t_env	*copy_list(t_env *src)
{
	t_env	*dst;
	t_env	*start;

	dst = NULL;
	start = dst;
	while (src != NULL)
	{
		dst = new_node(src->var);
		src = src->next;
		dst = dst->next;
	}
	return (start);
}
*/

t_env	*copy_list(t_env *src)
{
	t_env	*dst;

	dst = NULL;
	while (src != NULL)
	{
		_append_env_list(&dst, src->var);
		src = src->next;
	}
	return (dst);
}

void	swap(char **a, char **b)
{
	char	*t;

	t = *a;
	*a = *b;
	*b = t;
}

void	*tcs(t_env *p1, t_env *p2, int i)
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

void	*sort_alphabetically(t_env *copy)
{
	return (tcs(copy, copy->next, 0));
}

void	_delete_env_list(t_env **env_list)
{
	t_env	*t;

	while (*env_list != NULL)
	{
		t = (*env_list)->next;
		//free((*env_list)->var);
		free(*env_list);
		*env_list = t;
	}
}

void	delete_env_list(void)
{
	_delete_env_list(env_list(get));
}

t_env	*declare_x(t_env **env_list)
{
	t_env	*env_list_copy;

	env_list_copy = copy_list(*env_list);
	sort_alphabetically(env_list_copy);
	_print_env_list(env_list_copy); // add "declare -x" being printed before every env
	_delete_env_list(&env_list_copy);
	return ((t_env *)0xDEFEC8ED);
}

t_env	*export_var(t_ast *export_node)
{
	if (export_node->right == NULL)
		return (declare_x(env_list(get)));
	while (export_node->right != NULL)
	{
		append_env_list(export_node->right->data);
		export_node = export_node->right;
	}
	return (*env_list(get));
}

void	unset(t_ast *unset_node)
{

}

static char	*_get_env(t_env *list, char *var)
{
	while (list != NULL)
	{
		if (strcmp(list->var, var) == 0)
			return (list->var);
		list = list->next;
	}
	return (NULL);
}

char	*get_env(char *var)
{
	return (_get_env(*env_list(get), var));
}

int	main(int ac, char **av, char **envp)
{
	//t_ast *what = calloc(sizeof(t_ast), 1);
	//what->right = calloc(sizeof(t_ast), 1);
	//what->right->data = "biba=boba";
	create_env_list(envp);
	printf("%s\n", get_env("LESS"));
	//print_env_list();
	//printf("\n\n===\n\n");
	//export_var(what);
	//print_env_list();
}
