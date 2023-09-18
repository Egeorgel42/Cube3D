# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ory <ory@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 11:16:23 by egeorgel          #+#    #+#              #
#    Updated: 2023/09/18 14:56:14 by ory              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRC = main.c \
parsing/get_params.c \
parsing/error.c \
parsing/param.c \
utils/param_utils.c \
utils/utils.c \
parsing/get_map.c \
parsing/minimap_initialize.c\
parsing/map_parse.c \
utils/mlx_image.c \
game/keys.c \
game/movement.c\
render/render.c \
render/draw.c\
render/init_render.c\

SRC_BONUS = bonus/minimap_update_bonus.c\
	bonus/main_bonus.c\
	parsing/get_params.c \
	parsing/error.c \
	parsing/param.c \
	utils/param_utils.c \
	utils/utils.c \
	parsing/get_map.c \
	parsing/map_parse.c \
	parsing/minimap_initialize.c\
	utils/mlx_image.c \
	game/keys.c \
	game/movement.c\
	render/render.c \
	render/draw.c\
	render/init_render.c\

OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

#LFLAGS = -Llibft -lft -lmlx_Linux -lXext -lX11 -lm -lz
#for linux
LFLAGS = -Lminilibx_opengl -lmlx -framework OpenGL -framework AppKit -Llibft -lft
#for Macos
#uncomment whichever flag is needed depending on your OS

CFLAGS = -Wall -Wextra -Werror -g -I. #-fsanitize=address
LIBFT = libft/libft.a
HDR = cub3d.h
HDRB = cub3d_bonus.h
NAME = cub3D
NAME_BONUS = cub3D_bonus

all: $(NAME)

$(NAME):$(OBJ) 
	@make -C ./libft bonus
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)

$(NAME_BONUS): $(OBJ_BONUS)
	@make -C ./libft bonus
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) $(LFLAGS)

.c.o: $(HDR) Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

bonus: $(NAME_BONUS)

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	cd libft && make clean;

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean flcean re