#include "env.h"
#include "../utils/utils.h"
#include "../parser/automata/nfa.h"

t_env	*_append_env_list(t_env **list, char *var, char *val)
{
	if (*list == NULL)
		return (*list = new_env_node(var, val));
	return (_append_env_list(&((*list)->next), var, val));
}

static int	replace_old_env(t_env *env, char *val)
{
	free(env->val);
	env->val = ft_strdup(val);
	return (0);
}

int	append_env_list(char *var, char *val)
{
	t_env	*env;

	if (get_lexeme_len(export_automaton(), var) != ft_strlen(var))
		return (1);
	env = find_env_var(var);
	if (env)
		return (replace_old_env(env, val));
	_append_env_list(get_env_list_addr(), var, val);
	return (0);
}
