# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 11:16:23 by egeorgel          #+#    #+#              #
#    Updated: 2023/07/20 11:52:26 by egeorgel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRC = main.c
OBJ = ${SRC:.c=.o}

LFLAGS = -Llibft -lft -lmlx_Linux -lXext -lX11 -lm -lz
#for linux
#LFLAGS = -lmlx -framework OpenGL -framework AppKit
#for Macos
#uncomment whichever flag is needed depending on your OS

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LIBFT = libft/libft.a
HDR = cube3d.h
NAME = Cube3D

all: $(NAME)

$(LIBFT):
	cd libft && make bonus;

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

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