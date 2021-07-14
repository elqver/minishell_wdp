NAME		= minishell

objs		= main.o \
			  tokenizer.o append_token_list.o \
			  resect_quotes.o replace_substring.o \
			  print_token_list.o \
			  \
				nfa.o transition.o				\
				word_automaton.o pipe_automaton.o redir_automaton.o	\
				single_quote_automaton.o double_quote_automaton.o	\
				heredoc_automaton.o env_automaton.o dollar_env_automaton.o \
				export_automaton.o \
				ft_string.o	\
				command_command.o command_pipe.o command_redir.o \
				\
				ast_singleton.o \
				ast.o create_ast_node.o insert_ast_node.o \
				print_ast.o choose_color.o \
				heredoc.o handle_heredoc_node.o \
				\
				env_singleton.o new_env_node.o create_env_list.o declare_x.o \
				array_from_list.o append_env_list.o split_append_env.o env_substr.o \
				echo.o cd.o pwd.o env_export.o unset.o env_print.o wdp_exit.o \
				print_env_list.o find_env_var.o \
				handle_envs.o find_env_val.o \
				word_symbol.o single_quotes.o double_quotes.o redir.o \
				pipe.o space.o dollar.o env_symbol.o \
				delete_env_list.o delete_env_node.o \
				signal_modes.o

VPATH		= ast:\
				parser/automata::parser/transition:parser/conditions: \
				command:tokenizer:utils:builtins: \
				signals

CC			= clang

CFLAGS		= #-Wall -Werror -Wextra

DEBUG		= -g

READLINE	= -lreadline -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ \
				-I/Users/$(USER)/.brew/Cellar/readline/8.1/include

all:		$(NAME)

deps		= $(patsubst %.o,%.d,$(objs))
-include	$(deps)
DEPFLAGS	= -MMD -MF $(@:.o=.d)

$(NAME):	$(objs)
			$(CC) $(CFLAGS) $(DEBUG) $(READLINE) $^ -o $@

%.o:		%.c
			$(CC) $(CFLAGS) $(DEBUG) -c $< $(DEPFLAGS)

clean:
			rm -rf $(objs) $(deps)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all deps clean fclean re
