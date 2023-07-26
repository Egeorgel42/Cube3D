# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 11:16:23 by egeorgel          #+#    #+#              #
#    Updated: 2023/07/26 15:15:53 by egeorgel         ###   ########.fr        #
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
parsing/map_parse.c
OBJ = ${SRC:.c=.o}

#LFLAGS = -Llibft -lft -lmlx_Linux -lXext -lX11 -lm -lz
LFLAGS = -Lminilibx_opengl -lmlx -framework OpenGL -framework AppKit -Llibft -lft
#for linux 
#LFLAGS = -lmlx -framework OpenGL -framework AppKit
#for Macos
#uncomment whichever flag is needed depending on your OS

CFLAGS = -Wall -Wextra -Werror -g -I. #-fsanitize=address
LIBFT = libft/libft.a
HDR = cub3d.h
NAME = Cub3D

all: $(NAME)

# $(LIBFT):
# 	cd libft && $(MAKE) bonus;

$(NAME):$(OBJ) 
	@make -C minilibx_opengl/ all
	@make -C ./libft bonus
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	$(MAKE) clean

# $(NAME): ${OBJ}
# 	@make -C minilibx_opengl/ all
# 	@make -C ./libft/
# 	gcc $(OBJ) -o $(NAME) $(CFLAGS) ./libft/libft.a minilibx_opengl/libmlx.a $(LFLAGS) -g 

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
