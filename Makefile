# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skern <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 17:40:42 by skern             #+#    #+#              #
#    Updated: 2021/05/08 20:07:27 by skern            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= calc

SRCS		= ast.c ast_node.c tokenizer.c \
			  mul_ast_node.c plus_ast_node.c num_ast_node.c main.c

OBJS		= ${SRCS:.c=.o}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

%.c.o:
			$(CC) ${CFLAGS} $< -o ${<:.c=.o} -g

${NAME}:	$(OBJS)
			$(CC) ${CFLAGS} ${OBJS} -o ${NAME} -g

all:		${NAME}

clean:		
			rm -f ${OBJS}
			rm -f ${OBJS:.o=.d}

fclean:		clean
			rm ${NAME}

re:			fclean all
