#include "env.h"
#include "env_substr.h"

t_env	**env_list(t_env **(* action)(t_env **))
{
	static t_env	*env_list;

	return (action(&env_list));
}

t_env	**get(t_env **env_list)
{
	return (env_list);
}

t_env	*new_env_node(char *var, char *val)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->var = strdup(var); // TODO: replace with ft_ and check for NULL
	new->val = strdup(val); // TODO: replace with ft_
	new->next = NULL;
	return (new);
}

static t_env	*_append_env_list(t_env **list, char *var, char *val)
{
	if (*list == NULL)
		return (*list = new_env_node(var, val));
	return (_append_env_list(&((*list)->next), var, val));
}

t_env	*append_env_list(char *var, char *val)
{
	return (_append_env_list(env_list(get), var, val));
}

t_env	*split_append_env(t_env **list, char *env)
{
	char	*var;
	char	*val;
	t_env	*new_env;

	var = var_substr(env);
	if (var == NULL)
		return (NULL);
	val = val_substr(env);
	if (val == NULL)
	{
		free(var);
		return (NULL);
	}
	new_env = _append_env_list(list, var, val);
	free(var);
	free(val);
	return (new_env);
}

static void	_create_env_list(t_env **list, char **envp)
{
	unsigned int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		split_append_env(list, envp[i]);
		i++;
	}
}

void	create_env_list(char **envp)
{
	_create_env_list(env_list(get), envp);
}

void	print_env(char *var, char *val)
{
	write(1, var, strlen(var)); // TODO: replace with ft_
	write(1, "=", 1);
	write(1, val, strlen(val)); // TODO:
	write(1, "\n", 1);
}

static void	_print_env_list(t_env *list)
{
	while (list != NULL)
	{
		print_env(list->var, list->val);
		list = list->next;
	}
}

void	print_env_list(void)
{
	_print_env_list(*env_list(get));
}

void	env(t_ast *node)
{
	(void)node;
	print_env_list();
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

void	delete_env_list(void)
{
	_delete_env_list(env_list(get));
}

int	main(int ac, char **av, char **envp)
{
	create_env_list(envp);
	print_env_list();
	delete_env_list();
}
