#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include "../ast.h"

// TODO: delete
#include <string.h>
#include <stdio.h>

typedef struct		s_env
{
	char		*var;
	char		*val;
	struct s_env	*next;
}			t_env;

t_env	**env_list(t_env **(* action)(t_env **));
t_env	**get(t_env **env_list);
t_env	*new_env_node(char *var, char *val);
t_env	*append_env_list(char *var, char *val);
void	create_env_list(char **envp);
void	delete_env_list(void);

//t_env	*split_append_env(t_env **list, char *env);
t_env	*split_append_env(char *env);
void	print_env_list(void);
void	print_env(char *var, char *val);

t_ast	*minish_export(t_ast *node);
t_ast	*declare_x(void);

#endif
