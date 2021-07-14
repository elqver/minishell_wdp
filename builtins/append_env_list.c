#include "env.h"
#include "../parser/automata/nfa.h"

#include <ctype.h> // TODO: delete

t_env	*_append_env_list(t_env **list, char *var, char *val)
{
	if (*list == NULL)
		return (*list = new_env_node(var, val));
	return (_append_env_list(&((*list)->next), var, val));
}

static int	replace_old_env(t_env *env, char *val)
{
	free(env->val);
	// When we include libft,
	// the if-else won't be needed.
	// env->val = ft_strdup(val);
	if (val == NULL)
		env->val = NULL;
	else
		env->val = strdup(val); // TODO: replace with ft_
	return (0);
}

int	append_env_list(char *var, char *val)
{
	t_env	*env;

	if (get_lexeme_len(export_automaton(), var) != strlen(var)) // TODO: ft_
		return (1);
	env = find_env_var(var);
	if (env)
		return (replace_old_env(env, val));
	_append_env_list(get_env_list_addr(), var, val);
	return (0);
}
