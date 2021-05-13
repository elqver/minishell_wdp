#ifndef AUTOMATA_H
# define AUTOMATA_H

# include "nfa.h"
# include "transition.h"

# include <string.h>					// TODO: replace

t_state	*word_automaton(void);
t_state	*redir_automaton(void);
t_state	*pipe_automaton(void);

#endif