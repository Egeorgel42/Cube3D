# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 11:16:23 by egeorgel          #+#    #+#              #
#    Updated: 2023/09/20 17:30:21 by egeorgel         ###   ########.fr        #
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
	bonus/parsing/get_params.c \
	bonus/parsing/error.c \
	bonus/parsing/param.c \
	bonus/utils/param_utils.c \
	bonus/utils/utils.c \
	bonus/parsing/get_map.c \
	bonus/parsing/map_parse.c \
	bonus/parsing/minimap_initialize.c\
	bonus/utils/mlx_image.c \
	bonus/game/keys.c \
	bonus/game/movement.c\
	bonus/render/render.c \
	bonus/render/draw.c\
	bonus/render/init_render.c\

OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

LFLAGS = -Llibft -lft -Lminilibx -lmlx_Linux -lXext -lX11 -lm -lz
#for linux
#LFLAGS = -Lminilibx -lmlx -framework OpenGL -framework AppKit -Llibft -lft
#for Macos
#uncomment whichever flag is needed depending on your OS

CFLAGS = -Wall -Wextra -Werror -g -I. #-fsanitize=address
LIBFT = libft/libft.a
HDR = cub3d.h
HDRB = cub3d_bonus.h
NAME = cub3D

ifndef WithBonus
	OBJS = $(OBJ)
else
	OBJS = $(OBJ_BONUS)
endif

all: $(NAME)

$(LIBFT):
	@make -C ./libft bonus

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)
ifndef WithBonus
	rm -f $(OBJ_BONUS)
else
	rm -f $(OBJ)
endif

.c.o: $(HDR) Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

bonus:
	@make WithBonus=1

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	cd libft && make clean;

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean flcean re bonus