# # **************************************************************************** #
# #                                                                              #
# #                                                         :::      ::::::::    #
# #    Makefile                                           :+:      :+:    :+:    #
# #                                                     +:+ +:+         +:+      #
# #    By: ory <ory@student.42.fr>                    +#+  +:+       +#+         #
# #                                                 +#+#+#+#+#+   +#+            #
# #    Created: 2023/07/20 11:16:23 by egeorgel          #+#    #+#              #
# #    Updated: 2023/07/25 15:29:27 by ory              ###   ########.fr        #
# #                                                                              #
# # **************************************************************************** #

CC = gcc
SRC = main.c \
parsing/get_params.c \
parsing/error.c \
parsing/param.c \
utils/param_utils.c \
utils/utils.c \
parsing/get_map.c\

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

$(NAME):$(OBJ) 
	@make -C minilibx_opengl/ all
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
