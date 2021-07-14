#ifndef SIGNAL_MODES_H
# define SIGNAL_MODES_H

# include <signal.h>
# include <readline/readline.h>

void	rl_replace_line(char *a, int b);

void	switch_to_interactive_mode(void);
void	switch_to_command_mode(void);
void	switch_to_heredoc_mode(void);

#endif
