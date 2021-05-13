#ifndef AUTOMATA_H
# define AUTOMATA_H

# include "nfa.h"
# include "transition.h"

# include <string.h>					// TODO: replace
# include <ctype.h>						// TODO: replace

t_state	*word_automaton(void);
t_state	*single_quote_automaton(void);
t_state	*double_quote_automaton(void);

t_state	*redir_automaton(void);
t_state	*pipe_automaton(void);

#endif
