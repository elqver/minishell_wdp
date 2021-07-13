NAME		= minishell

objs		= main.o tokenizer.o nfa.o transition.o				\
   			   word_automaton.o pipe_automaton.o redir_automaton.o	\
			   single_quote_automaton.o double_quote_automaton.o	\
			   heredoc_automaton.o \
			   ft_string.o	\
			   command_command.o command_pipe.o command_redir.o \
			   ast.o \
			   \
			   env_singleton.o new_env_node.o create_env_list.o declare_x.o \
			   array_from_list.o append_env_list.o split_append_env.o env_substr.o \
			   echo.o cd.o pwd.o env_export.o unset.o env_print.o wdp_exit.o \
			   print_env_list.o find_env_var.o \
			   handle_envs.o find_env_val.o \
			   word_symbol.o single_quotes.o double_quotes.o redir.o \
			   pipe.o space.o dollar.o env_symbol.o \
			   delete_env_node.o env_automaton.o \
			   modes.o

VPATH		= ast:automata/automata:automata/nfa:automata/transition: \
			   automata/conditions:command:tokenizer:utils:builtins: \
			   signals

CC			= gcc

#CFLAGS		= -Wall -Werror -Wextra

DEBUG		= -g

READLINE	= -lreadline -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ \
				-I/Users/$(USER)/.brew/Cellar/readline/8.1/include

all:		$(NAME)

deps		= $(patsubst %.o,%.d,$(objs))
-include	$(deps)
DEPFLAGS	= -MMD -MF $(@:.o=.d)

$(NAME):	$(objs)
			$(CC) $(DEBUG) $(READLINE) $^ -o $@

%.o:		%.c
			$(CC) $(DEBUG) -c $< $(DEPFLAGS)

clean:
			rm -rf $(objs) $(deps)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all deps clean fclean re
