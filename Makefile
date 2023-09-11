# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 11:16:23 by egeorgel          #+#    #+#              #
#    Updated: 2023/09/11 16:20:08 by egeorgel         ###   ########.fr        #
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
parsing/map_parse.c \
parsing/minimap_initialize.c \
game/minimap_update.c \
utils/mlx_image.c \
game/keys.c \
game/movement.c\
render/render.c \

OBJ = ${SRC:.c=.o}

#LFLAGS = -Llibft -lft -lmlx_Linux -lXext -lX11 -lm -lz
#for linux
LFLAGS = -Lminilibx_opengl -lmlx -framework OpenGL -framework AppKit -Llibft -lft
#for Macos
#uncomment whichever flag is needed depending on your OS

CFLAGS = -Wall -Wextra -Werror -g -I. #-fsanitize=address
LIBFT = libft/libft.a
HDR = cub3d.h
NAME = cub3D

all: $(NAME)

$(NAME):$(OBJ) 
	@make -C ./libft bonus
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	$(MAKE) clean

.c.o: $(HDR) Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)
	cd libft && make clean;

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean flcean re
