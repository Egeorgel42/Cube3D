# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 11:16:23 by egeorgel          #+#    #+#              #
#    Updated: 2023/07/21 18:11:30 by egeorgel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRC = main.c \
parsing/get_params.c \
parsing/error.c \
parsing/param.c \
utils/param_utils.c
OBJ = ${SRC:.c=.o}

LFLAGS = -Llibft -lft -lmlx_Linux -lXext -lX11 -lm -lz
#for linux
#LFLAGS = -lmlx -framework OpenGL -framework AppKit
#for Macos
#uncomment whichever flag is needed depending on your OS

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -I.
LIBFT = libft/libft.a
HDR = cub3d.h
NAME = Cub3D

all: $(NAME)

$(LIBFT):
	cd libft && $(MAKE) bonus;

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)
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