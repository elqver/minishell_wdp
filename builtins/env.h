#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include "../ast/ast.h"

// TODO: delete
#include <string.h>
#include <stdio.h>

typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*next;
}				t_env;

t_env	**env_list(t_env **(*action)(t_env **));
t_env	**get(t_env **env_list);
t_env	*new_env_node(char *var, char *val);
int		append_env_list(char *var, char *val);
t_env	*_append_env_list(t_env **list, char *var, char *val);
void	create_env_list(char **envp);
int		delete_env_node(t_env **node);
void	delete_env_list(void);
void	_delete_env_list(t_env **list);
t_env	*find_env_var(char const *name);
char	*find_env_val(char const *name);
int		split_append_env(char *env);
void	print_env_list(void);
void	print_env(char *var, char *val);
int		declare_x(void);
char	**array_from_list(t_env *env);
void	delete_env_arr(char **env_arr);

#endif
