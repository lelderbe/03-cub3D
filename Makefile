# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 12:10:28 by lelderbe          #+#    #+#              #
#    Updated: 2021/01/12 12:19:28 by lelderbe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= cub3D.c

HEADERS		= cub3D.h

OBJS		= ${SRCS:.c=.o}

NAME		= cub3D.out

LIBFT_DIR	= libft

CC			= gcc

AR			= ar

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

%.o:		%.c ${HEADERS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

#${NAME}:	LIBFT ${OBJS}
${NAME}:	${OBJS}
			${CC} ${OBJS} -o ${NAME}
			#${CC} ${OBJS} -L${LIBFT_DIR} -lft -o ${NAME}
			#cp ${LIBFT_DIR}/${LIBFT_NAME} ${NAME}
			#${AR} rc ${NAME} ${OBJS}

LIBFT:		RULE
			${MAKE} -C ${LIBFT_DIR} all

RULE:

bonus:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} -C ${LIBFT_DIR} clean

fclean:		clean
			${RM} ${NAME}
			${MAKE} -C ${LIBFT_DIR} fclean
#			cd libft && ${MAKE} fclean

re:			fclean all

.PHONY:		all clean fclean re
