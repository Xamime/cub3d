# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxime <maxime@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 15:33:31 by mdesrose          #+#    #+#              #
#    Updated: 2023/11/18 15:29:25 by maxime           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	srcs/dda.c \
		srcs/debug.c \
		srcs/draw_utils.c \
		srcs/draw.c \
		srcs/get_files_path.c \
		srcs/init.c \
		srcs/main.c \
		srcs/moving.c \
		srcs/parse_map.c \
		srcs/parsing.c \
		srcs/pixel.c \
		srcs/render_textures.c \
		srcs/textures.c \
		srcs/utils.c 

SRC_BONUS =	srcsbonus/dda_bonus.c \
			srcsbonus/debug_bonus.c \
			srcsbonus/draw_utils_bonus.c \
			srcsbonus/draw_bonus.c \
			srcsbonus/get_files_path_bonus.c \
			srcsbonus/init_bonus.c \
			srcsbonus/main_bonus.c \
			srcsbonus/moving_bonus.c \
			srcsbonus/parse_map_bonus.c \
			srcsbonus/parsing_bonus.c \
			srcsbonus/pixel_bonus.c \
			srcsbonus/render_textures_bonus.c \
			srcsbonus/textures_bonus.c \
			srcsbonus/utils_bonus.c \
			srcsbonus/draw_minimap_bonus.c

NAME = cub3d
NAMEB = cub3d_bonus
LIBFT_SRC = libft
MLX_DIR = MLX42
LIBFT = ${LIBFT_SRC}/libft.a
LIBMLX = ${MLX_DIR}/build/libmlx42.a
LIBS = $(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm
INCLUDES = -I ./
CC = clang
CFLAGS = #-Wall -Wextra -Werror -Iincludes -g
OBJ = $(SRC:c=o)
OBJB = $(SRC_BONUS:c=o)

YELLOW=\033[0;33m
GREEN=\033[0;32m
RED=\033[0;31m
DEFAULT=\033[39m
CLEANL=\r\033[K

all: $(NAME)

bonus: $(NAMEB)

%.o: %.c
	${CC} ${CFLAGS} -I/usr/include -c $< -o $@ -O3

$(NAME): $(OBJ) $(LIBFT) libmlx
	$(CC) -Iincludes $(OBJ) $(LIBS) -o $(NAME) -O3

$(NAMEB): $(OBJB) $(LIBFT) libmlx
	$(CC) -Iincludes $(OBJB) $(LIBS) -o $(NAMEB) -O3

libmlx:
	cmake -DDEBUG=1 $(MLX_DIR) -B $(MLX_DIR)/build && cmake --build $(MLX_DIR)/build -j8

${LIBFT}:
	make all -C ${LIBFT_SRC} -s

clean:
	rm -f $(OBJ)
	rm -f $(OBJB)
	make clean -C ${LIBFT_SRC} -s

fclean: clean
	rm -f $(NAME)
	rm -f $(NAMEB)
	rm -rf $(MLX_DIR)/build
	make fclean -C ${LIBFT_SRC} -s

re: fclean all

wlib_fclean:
	rm -f $(OBJ)
	rm -f $(NAME)
	rm -f $(OBJB)
	rm -f $(NAMEB)

wlib: wlib_fclean all

.PHONY: clean fclean re bonus
