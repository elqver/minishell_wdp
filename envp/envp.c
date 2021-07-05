#include "envp.h"

t_env	**_env_list(t_env *root)
{
	static t_env	*env_list;

	if (env_list == NULL && root)
		env_list = root;
	return (&env_list);
}

t_env	*_get_env_list(void)
{
	return (*_env_list(NULL));
}

t_env	*_new_env_node(char *var, char *val)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->var = strdup(var);
	new->val = strdup(val);
	new->next = NULL;
	return (new);
}

t_env			*append_env_list(char *var, char *val)
{
	t_env	*node;
	t_env	*p;

	node = _new_env_node(var, val);
	p = _get_env_list();
	if (p == NULL)
	{
		_env_list(node);
		return (node);
	}
	while (p->next)
		p = p->next;
	p->next = node;
	return (node);
}

// TODO:
// there's a lot of libft functions here
// that need to be replaced with ft_ analogs

static char	*_substr(char *str, char *start, char *end)
{
	char	*sub;

	if (str == NULL || start == NULL || end == NULL)
		return (NULL);
	sub = calloc(sizeof(char), end - start + 1);
	if (sub == NULL)
		return (NULL);
	sub = strncpy(sub, start, end - start);
	return (sub);
}

char	*var_substr(char *str)
{
	return (_substr(str, str, strchr(str, '=')));
}

char	*val_substr(char *str)
{
	return (_substr(str, strchr(str, '=') + 1, strchr(str, '\0')));
}

t_env	*split_append_env(char *env)
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
	new_env = append_env_list(var, val);
	free(var);
	free(val);
	return (new_env);
}

void	create_env_list(char **envp)
{
	unsigned int	i;

	i = 0;
	while (envp[i] != NULL)
		split_append_env(envp[i++]);
}

void	delete_env_list(void)
{
	t_env	*list;
	t_env	*t;

	list = _get_env_list();
	while (list != NULL)
	{
		t = list->next;
		free(list->var);
		free(list->val);
		free(list);
		list = t;
	}
}

void	print_env_list()
{
	t_env	*env_list;

	env_list = _get_env_list();
	while (env_list != NULL)
	{
		printf("%s=%s\n", env_list->var, env_list->val);
		env_list = env_list->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	create_env_list(argv);
	print_env_list();
	delete_env_list();
	printf("after delete\n");
}
