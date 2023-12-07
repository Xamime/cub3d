# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 15:33:31 by mdesrose          #+#    #+#              #
#    Updated: 2023/12/07 19:45:57 by jfarkas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =		srcs/check_map.c \
			srcs/dda.c \
			srcs/draw_utils.c \
			srcs/draw.c \
			srcs/init.c \
			srcs/main.c \
			srcs/moving.c \
			srcs/parse_background.c \
			srcs/parse_map.c \
			srcs/parse_textures.c \
			srcs/parsing.c \
			srcs/render_textures.c \
			srcs/textures.c \
			srcs/utils.c \
			srcs/utils2.c \
			srcs/utils3.c

SRC_BONUS =	srcs_bonus/check_map_bonus.c \
			srcs_bonus/dda_bonus.c \
			srcs_bonus/door_collisions_bonus.c \
			srcs_bonus/doors_bonus.c \
			srcs_bonus/draw_bonus.c \
			srcs_bonus/draw_minimap_bonus.c \
			srcs_bonus/draw_utils_bonus.c \
			srcs_bonus/hooks_bonus.c \
			srcs_bonus/init_bonus.c \
			srcs_bonus/init2_bonus.c \
			srcs_bonus/main_bonus.c \
			srcs_bonus/moving_bonus.c \
			srcs_bonus/object_map_bonus.c \
			srcs_bonus/parse_background_bonus.c \
			srcs_bonus/parse_map_bonus.c \
			srcs_bonus/parse_textures_bonus.c \
			srcs_bonus/parsing_bonus.c \
			srcs_bonus/render_textures_bonus.c \
			srcs_bonus/textures_bonus.c \
			srcs_bonus/utils_bonus.c \
			srcs_bonus/utils2_bonus.c \
			srcs_bonus/utils3_bonus.c

NAME = cub3d
NAMEB = cub3d_bonus
LIBFT_SRC = libft
MLX_DIR = MLX42
LIBFT = ${LIBFT_SRC}/libft.a
LIBMLX = ${MLX_DIR}/build/libmlx42.a
LIBS = $(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm
CC = clang
CFLAGS = -g -Wall -Wextra -Werror -Iincludes
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
	$(CC) ${CFLAGS} $(OBJ) $(LIBS) -o $(NAME) -O3

$(NAMEB): $(OBJB) $(LIBFT) libmlx
	$(CC) ${CFLAGS} $(OBJB) $(LIBS) -o $(NAMEB) -O3

libmlx:
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && cmake --build $(MLX_DIR)/build -j8

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
