NAME		= minishell

objs		= main.o tokenizer.o nfa.o transition.o				\
   			   word_automaton.o pipe_automaton.o redir_automaton.o	\
			   single_quote_automaton.o double_quote_automaton.o	\
			   ft_string.o	\
			   command_command.o command_pipe.o command_redir.o \
			   ast.o

#VPATH		= .

CC			= gcc

#CFLAGS		= -Wall -Werror -Wextra

DEBUG		= -g

all:		$(NAME)

deps		= $(patsubst %.o,%.d,$(objs))
-include	$(deps)
DEPFLAGS	= -MMD -MF $(@:.o=.d)

$(NAME):	$(objs)
			$(CC) $(DEBUG) $^ -o $@

%.o:		%.c
			$(CC) $(DEBUG) -c $< $(DEPFLAGS)

clean:
			rm -rf $(objs) $(deps)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all deps clean fclean re
