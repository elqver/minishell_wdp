# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skern <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 17:40:42 by skern             #+#    #+#              #
#    Updated: 2021/05/08 20:15:44 by skern            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= calc

SRCS		= ast.c ast_node.c tokenizer.c \
			  mul_ast_node.c plus_ast_node.c num_ast_node.c main.c

OBJS		= ${SRCS:.c=.o}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g 

%.c.o:
			$(CC) ${CFLAGS} $< -o ${<:.c=.o}

${NAME}:	$(OBJS)
			$(CC) ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:		
			rm -f ${OBJS}

fclean:		clean
			rm ${NAME}

re:			fclean all
