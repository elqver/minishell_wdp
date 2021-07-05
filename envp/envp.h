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


// private_env.h
// Private:
t_env	**_env_list(t_env *root);
t_env	*_get_env_list(void);
t_env	*_new_env_node(char *var, char *val);

// env.h
// Public:
t_env	*append_env_list(char *var, char *val);
t_env	*split_append_env(char *env);
void	create_env_list(char **envp);
void	delete_env_list(void);
void	print_env_list(void);

