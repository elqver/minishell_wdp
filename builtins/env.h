#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include "../ast/ast.h"

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

t_env	*find_env_var(char const *name);
char	*find_env_val(char const *name);

//t_env	*split_append_env(t_env **list, char *env);
t_env	*split_append_env(char *env);
void	print_env_list(void);
void	print_env(char *var, char *val);
//void	env(t_ast *node);

//t_ast	*env_export(t_ast *node);
t_ast	*declare_x(void);

char	**array_from_list(t_env *env);
void	delete_env_arr(char **env_arr);

#endif
