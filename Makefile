# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: max <max@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 15:33:31 by mdesrose          #+#    #+#              #
#    Updated: 2023/10/16 14:09:42 by max              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = $(wildcard *.c)

NAME = cub3d
LIBFT_SRC = libft
MLX_DIR = MLX42
LIBFT = ${LIBFT_SRC}/libft.a
LIBMLX = ${MLX_DIR}/build/libmlx42.a 
LIBS = $(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm -lglfw
INCLUDES = -I ./
CC = clang
CFLAGS = -Iincludes
OBJ = $(SRC:c=o)

YELLOW=\033[0;33m
GREEN=\033[0;32m
RED=\033[0;31m
DEFAULT=\033[39m
CLEANL=\r\033[K

all: $(NAME)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) libmlx 
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

libmlx:
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && cmake --build $(MLX_DIR)/build -j4

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

.PHONY: clean fclean re