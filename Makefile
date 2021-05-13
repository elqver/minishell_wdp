NAME		:= minishell

objs		:= main.o tokenizer.o nfa.o transition.o \
   			   word_automaton.o pipe_automaton.o redir_automaton.o

#VPATH		:= .

CC			:= gcc

#CFLAGS		:= -Wall -Werror -Wextra

DEBUG		:= -g

all:		$(NAME)

deps		:= $(patsubst %.o,%.d,$(objs))
-include	$(deps)
DEPFLAGS	:= -MMD -MF $(@:.o=.d)

$(NAME):	$(objs)
			$(CC) $(DEBUG) $^ -o $@

$.o:		%.c
			$(CC) $(DEBUG) -c $< $(DEPFLAGS)

clean:
			rm -rf $(objs) $(deps)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all deps clean fclean re
