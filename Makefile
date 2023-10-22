# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 15:33:31 by mdesrose          #+#    #+#              #
#    Updated: 2023/10/22 07:05:20 by jfarkas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = $(wildcard srcs/*.c)

NAME = cub3d
LIBFT_SRC = libft
MLX_DIR = MLX42
LIBFT = ${LIBFT_SRC}/libft.a
LIBMLX = ${MLX_DIR}/build/libmlx42.a
LIBS = $(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm
INCLUDES = -I ./
CC = clang
CFLAGS = #-Wall -Wextra -Werror -Iincludes -g
OBJ = $(SRC:c=o)

YELLOW=\033[0;33m
GREEN=\033[0;32m
RED=\033[0;31m
DEFAULT=\033[39m
CLEANL=\r\033[K

all: $(NAME)

%.o: %.c
	${CC} ${CFLAGS} -I/usr/include -c $< -o $@ -g

$(NAME): $(OBJ) $(LIBFT) libmlx
	$(CC) -Iincludes -g $(OBJ) $(LIBS) -o $(NAME)

libmlx:
	cmake -DDEBUG=1 $(MLX_DIR) -B $(MLX_DIR)/build && cmake --build $(MLX_DIR)/build -j8

${LIBFT}:
	make all -C ${LIBFT_SRC} -s

clean:
	rm -f $(OBJ)
	make clean -C ${LIBFT_SRC} -s

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_DIR)/build
	make fclean -C ${LIBFT_SRC} -s

re: fclean all

wlib_fclean:
	rm -f $(OBJ)
	rm -f $(NAME)

wlib: wlib_fclean all

.PHONY: clean fclean re
