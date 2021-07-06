#include "env.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;(void)av;

	create_env_list(envp);
	print_env_list();
	delete_env_list();
}
