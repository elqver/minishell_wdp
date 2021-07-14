#include "signal_modes.h"
#include "../ast/ast.h"
#include "../builtins/builtins.h"

static void	dummy(int beef)
{
	(void)beef;
}

void	switch_to_command_mode(void)
{
	signal(SIGQUIT, dummy);
	signal(SIGINT, dummy);
}
