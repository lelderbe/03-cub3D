# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 12:10:28 by lelderbe          #+#    #+#              #
#    Updated: 2021/03/09 18:13:37 by lelderbe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c \
			  parse.c parse_cub.c parse_map.c parse_sprites.c \
			  events.c engine_p1.c engine_p2.c \
			  graphics_2d_p1.c graphics_2d_p2.c \
			  graphics_3d.c sprites.c \
			  graphics_utils_p1.c graphics_utils_p2.c \
			  utils_p1.c utils_p2.c bmp.c \
			  ${GNL_DIR}get_next_line.c ${GNL_DIR}get_next_line_utils.c

HEADERS		= cub3d.h bmp.h

OBJS		= ${SRCS:.c=.o}

NAME		= cub3D

LIBFT_DIR	= libft/
MLX_DIR		= minilibx/
GNL_DIR		= gnl/

LIBFT		= libft.a
MLX			= libmlx.a

INCLUDES	= -I${LIBFT_DIR} -I${MLX_DIR} -I${GNL_DIR}

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -O2
MLXFLAGS	= -framework OpenGL -framework Appkit -O2

%.o:		%.c ${HEADERS}
			${CC} ${CFLAGS} ${INCLUDES} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${LIBFT_DIR}${LIBFT} ${MLX_DIR}${MLX} ${OBJS}
			${CC} ${OBJS} ${INCLUDES} -L${LIBFT_DIR} -lft -L${MLX_DIR} -lmlx ${MLXFLAGS} -o ${NAME}

${LIBFT_DIR}${LIBFT}:	${LIBFT_DIR}
			${MAKE} -C ${LIBFT_DIR} bonus

${MLX_DIR}${MLX}:		${MLX_DIR}
			${MAKE} -C ${MLX_DIR} all

bonus:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} -C ${LIBFT_DIR} clean
			${MAKE} -C ${MLX_DIR} clean

fclean:		clean
			${RM} ${NAME}
			${MAKE} -C ${LIBFT_DIR} fclean
#			cd libft && ${MAKE} fclean

re:			fclean all

.PHONY:		all clean fclean re
