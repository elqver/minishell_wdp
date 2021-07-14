#include "signal_modes.h"
#include "../ast/ast.h"
#include "../builtins/builtins.h"

static void	heredoc_mode_sigint_handler(int signo)
{
	(void)signo;
	exit(1);
}

void	switch_to_heredoc_mode(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_mode_sigint_handler);
}
