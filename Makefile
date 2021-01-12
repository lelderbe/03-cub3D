# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 12:10:28 by lelderbe          #+#    #+#              #
#    Updated: 2021/01/12 13:17:24 by lelderbe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c

HEADERS		= cub3d.h

OBJS		= ${SRCS:.c=.o}

NAME		= a.out
#NAME		= cub3D.out

LIBFT_DIR	= libft
LIBFT_NAME	= libft.a
MLX_DIR		= minilibx
MLX_NAME	= libmlx.a

CC			= gcc

AR			= ar

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror
MLXFLAGS	= -framework OpenGL -framework Appkit

%.o:		%.c ${HEADERS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

#${NAME}:	${OBJS}
${NAME}:	LIBFT MLX ${OBJS}
			#${CC} ${OBJS} -o ${NAME}
			${CC} ${OBJS} -L${LIBFT_DIR} -lft -L${MLX_DIR} -lmlx ${MLXFLAGS} -o ${NAME}
			#cp ${LIBFT_DIR}/${LIBFT_NAME} ${NAME}
			#${AR} rc ${NAME} ${OBJS}

LIBFT:		RULE
			${MAKE} -C ${LIBFT_DIR} all

MLX:		RULE
			${MAKE} -C ${MLX_DIR} all

RULE:

bonus:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} -C ${LIBFT_DIR} clean
			${MAKE} -C ${MLX_DIR} clean

fclean:		clean
			${RM} ${NAME}
			${MAKE} -C ${LIBFT_DIR} fclean
			${MAKE} -C ${MLX_DIR} fclean
#			cd libft && ${MAKE} fclean

re:			fclean all

.PHONY:		all clean fclean re
