#include "modes.h"
#include "../ast/ast.h"
#include "../builtins/builtins.h"

static void	interactive_mode_sigint_handler(int no)
{
	(void)no;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	dummy(int beef)
{
	(void)beef;
}

void	switch_to_interactive_mode(void)
{
	signal(SIGQUIT, exit);
	signal(SIGINT, interactive_mode_sigint_handler); 
}

void	switch_to_command_mode(void)
{
	signal(SIGQUIT, dummy);
	signal(SIGINT, dummy);
}

static void	heredoc_mode_sigint_handler(int no)
{
	(void)no;
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(1);
}

void	switch_to_heredoc_mode()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_mode_sigint_handler);
}
